#include<SDL.h>
#include<stdio.h>

#include<stdbool.h>
#include<unistd.h>

#include"chip8.h"
#include"chip8_keyboard.h"


const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7,
    SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Must provide a file to load\n");
        return -1;
    }

    const char* filename = argv[1];
    printf("Loading %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if(!f){
        printf("Failure to open %s\n", filename);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char buf[size];
    int res = fread(buf, size, 1, f);
    if(res != 1){
        printf("Failure to read %s\n", filename);
        return -1;
    }

    struct chip8 chip8;
    chip8_init(&chip8);
    chip8_load(&chip8, buf, size);
    chip8_keyboard_set_map(&chip8.keyboard, keyboard_map);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    
    char close = 0;
    while(!close){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    {
                        char key = event.key.keysym.sym;
                        if(key == SDLK_ESCAPE){
                            close = 1;
                        }
                        else {
                            int vkey = chip8_keyboard_map(&chip8.keyboard, key);
                            chip8_keyboard_down(&chip8.keyboard, vkey);
                        }
                    }
                    break;
                case SDL_KEYUP:
                    {
                        char key = event.key.keysym.sym;
                        int vkey = chip8_keyboard_map(&chip8.keyboard, key);
                        chip8_keyboard_up(&chip8.keyboard, vkey);
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        for(int x = 0; x<CHIP8_WIDTH; x++){
            for(int y = 0; y<CHIP8_HEIGHT; y++){
                if(chip8_screen_is_set(&chip8.screen, x, y)){
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLIER;
                    r.y = y * CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }
        SDL_RenderPresent(renderer);
        if(chip8.registers.delay_timer > 0){
            usleep(1 * 1000);
            chip8.registers.delay_timer -= 1;
        }
        if(chip8.registers.sound_timer > 0){
            //TBD
            chip8.registers.sound_timer -= 1;
        }

        unsigned short opcode = chip8_memory_get_short(&chip8.memory, chip8.registers.PC);
        chip8.registers.PC += 2;
        printf("OPCODE: %X\n", opcode);
        printf("STACK: %d\n", chip8.registers.SP);
        chip8_exec(&chip8, opcode);
        usleep(1 * 1000);
    }
    SDL_DestroyWindow(window);
    return 0;
}