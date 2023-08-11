#include <iostream>
#include "cpu.hpp"
#include <SDL2/SDL.h>
#include <array>
#include "display.hpp"

CPU::CPU(){
  I = 0;
  PC = 0x200;
  SP = 0;
  DT = 0;
  ST = 0;
  font = {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2:
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
}

void CPU::load_font()
{
  for (int i = 80; i < 160; i++)
  {
    for (int j = 0; j < 81; j++)
      memory[i] = font[j];
  }
}

void CPU::graphics() {
  Window CPUDisplay;
  SDL_Event event;
  while(true) {
    SDL_PollEvent(&event);
    CPUDisplay.RenderFrame();
    switch(event.type) 
    {
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_1:
            std::cout << "1 pressed\n";
            break;/*
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
            break;*/
     }
    }
   }
  }

void CPU::init() {
  I = 0;
  load_font();
  graphics();
}
