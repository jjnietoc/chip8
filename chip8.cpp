#include <cstring>
#include <iostream>
#include "chip8.h"
#include <SDL2/SDL.h>
#include <array>
#include "display.h"

Chip8::Chip8(){
  I = 0;
  pc = 0x200;
  sp = 0;
  delay_timer = 0;
  sound_timer = 0;
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


void Chip8::load_font()
{
  for (int i = 0; i < 80; i++)
  {
    memory[i] = font[i];
  }
}

void Chip8::graphics() {
  Window Chip8Display;
  SDL_Event event;
  while(true) {
    SDL_PollEvent(&event);
    Chip8Display.RenderFrame();
   }
  }

void Chip8::init() {
  I = 0;
  load_font();
  graphics();
}

Chip8::~Chip8() 
{

}
