#include <iostream>
#include "chip8.hpp"
#include <SDL2/SDL.h>
#include <array>
#include "display.hpp"

void Chip8::populate_memory()
{
  for (int i = 80; i < 160; i++)
  {
    for (int j = 0; j < 81; j++)
      memory[i] = font[j];
  }
}

void Chip8::show_memory()
{
  for (int i = 80; i < 160; i++)
    std::cout << font[i];
  std::cout << std::endl;
}

void Chip8::gfx() {
  Window Chip8Display;
  SDL_Event event;
  while(true) {
    SDL_PollEvent(&event);
    Chip8Display.RenderFrame();
    switch(event.type) 
    {
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_1:
            std::cout << "1 pressed\n";
            break;
          case SDLK_2:
            std::cout << "2 pressed\n";
            break;
          case SDLK_3:
            std::cout << "3 pressed\n";
            break;
          case SDLK_4:
            std::cout << "4 pressed\n";
            break;
          case SDLK_q:
            std::cout << "q pressed\n";
            break;
          case SDLK_w:
            std::cout << "w pressed\n";
            break;
          case SDLK_e:
            std::cout << "e pressed\n";
            break;
          case SDLK_r:
            std::cout << "r pressed\n";
            break;
          case SDLK_a:
            std::cout << "a pressed\n";
             break;
          case SDLK_s:
            std::cout << "s pressed\n";
            break;
          case SDLK_d:
            std::cout << "d pressed\n";
            break;
          case SDLK_f:
            std::cout << "f pressed\n";
            break;
          case SDLK_z:
            std::cout << "z pressed\n";
            break;
          case SDLK_x:
            std::cout << "x pressed\n";
             break;
          case SDLK_c:
            std::cout << "c pressed\n";
            break;
          case SDLK_v:
            std::cout << "v pressed\n";
            break;
        }
    }
   }
  }

void Chip8::init() {
  I = 0;
  PC = 0;
 // stack = 0;
  // memory = 0;
  populate_memory();
  gfx();
}

/*void Chip8::game_loop() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDLK_w:
        std::cout << "w pressed\n";
    }
  }
} */
