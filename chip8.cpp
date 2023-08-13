#include <cstdint>
#include <cstring>
#include <iostream>
#include "chip8.h"
#include <SDL2/SDL.h>
#include <array>
#include "display.h"
#include <fstream>
#include <vector>

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
 
void Chip8::init() 
{
  I = 0;
  load_font();
  // load_rom("ibm.ch8");
  //graphics();
  }

void Chip8::load_rom(std::string const& path)
{
  std::ifstream rom(path, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type rom_size = rom.tellg();
  std::vector<std::uint8_t> buffer(rom_size);
  rom.seekg(0, std::ios::beg);
  rom.read(reinterpret_cast<char*>(buffer.data()), rom_size);
  for(int i = 0; i < rom_size; i++) {
    memory[i + 512] = buffer[i];
  }
}

void Chip8::cycle() 
{

  // TODO 
  // DONDE PONER SDL PARA QUE SE CREE Y FUNCIONE PARA TODOS
  // LOGRAR QUE EL ROM INGRESE CORRECTAMENTE A LA MEMORIA
  // LEER EL ROM Y QUE IDENTIFIQUE INSTRUCCIONES
  // LOGRAR VER EL LOGO DE IBM

  load_rom("/ibm.ch8");
  SDL_Window* display = nullptr;
  SDL_Renderer* renderer =  nullptr;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_CreateWindowAndRenderer(64*4, 32*4, 0, &display, &renderer);
  SDL_RenderSetScale(renderer, 10, 10);
 
  u_int16_t opcode = memory[pc] << 8 | memory[pc + 1];
  std::cout << memory[pc];
  pc += 2;

  u_int8_t x = (opcode >> 8) & 0x0F;
  u_int8_t y = (opcode >> 4) & 0x0F;
  u_int8_t nibble = opcode & 0x0F;
  u_int16_t nnn = opcode & 0x0FFF;
  u_int8_t kk = opcode & 0x0FF;

  switch(opcode & 0xF000)
  {
    case(0x0000):
      if(opcode == 0x00E0){
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
      } else if(opcode == 0x00EE){
          stack[sp--] = pc;
          std::cout << pc;
        }
    break;
    case(0x1000): // jump
      pc = nnn;
      break;
    case(0x2000): 
      stack[sp++] = pc;
      pc = nnn;
      std::cout << pc;
      break;
    case(0x6000): // set register vx
      V[x] = kk;
      break;
    case(0x7000): // add value to register vx
      V[x] += kk;
      break;
    case(0xA000): // set index to register I
      I = nnn;
      break;
    case(0xD000): // display
      // draw
      int cor_x = V[x & 63];
      int cor_y = V[y & 31];
      std::cout << cor_x << " " << cor_y << std::endl;
      SDL_SetRenderDrawColor(renderer,255,255,255,255);
      SDL_RenderDrawPoint(renderer, cor_x, cor_y);
      SDL_RenderPresent(renderer);
      break;
    
  }
}

Chip8::~Chip8() 
{

}
