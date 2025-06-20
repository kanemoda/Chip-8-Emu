#include <stdio.h>
#include <SDL.h>
#include "chip8.h"
#include "chip8_keyboard.h"
#include <stdbool.h>
#include <sound.h>

const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_4,
    SDLK_q,
    SDLK_w,
    SDLK_e,
    SDLK_r,
    SDLK_a,
    SDLK_s,
    SDLK_d,
    SDLK_f,
    SDLK_z,
    SDLK_x,
    SDLK_c,
    SDLK_v,
};

int main(int argc, char const *argv[])
{
    struct chip8 chip8;
    chip8_init(&chip8);
    chip8.registers.ST = 30;

    chip8_screen_draw_sprite(&chip8.screen, 62, 10, &chip8.memory.memory[CHIP8_FONTSET_START_ADDRESS], 5);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER,
        SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto out;
                break;

            case SDL_KEYDOWN:
            {
                int key = event.key.keysym.sym;
                char vkey = chip8_keyboard_map(keyboard_map, key);
                if (vkey != -1)
                {
                    chip8_keyboard_down(&chip8.keyboard, vkey);
                }
            }
            break;

            case SDL_KEYUP:
            {
                int key = event.key.keysym.sym;
                char vkey = chip8_keyboard_map(keyboard_map, key);
                if (vkey != -1)
                {
                    chip8_keyboard_up(&chip8.keyboard, vkey);
                }
            }
            break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int x = 0; x < CHIP8_WIDTH; x++)
        {
            for (int y = 0; y < CHIP8_HEIGHT; y++)
            {
                if (chip8_screen_is_set(&chip8.screen, x, y))
                {
                    SDL_Rect r = {
                    x * CHIP8_WINDOW_MULTIPLIER,
                    y * CHIP8_WINDOW_MULTIPLIER,
                    CHIP8_WINDOW_MULTIPLIER,
                    CHIP8_WINDOW_MULTIPLIER
                    };

                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer);

        if (chip8.registers.DT > 0)
        {
            SDL_Delay(100);
            chip8.registers.DT -=1;
            printf("Delay!!!\n");
        }

        if (chip8.registers.ST > 0)
        {
            Beep(1500, 100 * chip8.registers.ST);
            chip8.registers.ST = 0;
        }
        
        
    }

out:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
