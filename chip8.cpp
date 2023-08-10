#include <iostream>
#include "chip8.hpp"
#include <SDL2/SDL.h>
#include <array>
#include "display.hpp"

void Chip8::populate_memory() // protoype, need to define
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
