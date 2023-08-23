#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <SDL2/SDL.h>

#include "chip8.h"
#include "display.h"


Chip8::Chip8(){
  I = 0;
  pc = 512;
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
    memory[i] = font[i];
}

void Chip8::init() 
{
  // resetting values
  for(int i = 0; i < 16; i++)
  {
    stack[i] = 0;
    V[i] = 0;
  }

  pc = 0x200;
  sp = 0;
  I = 0;
  delay_timer = 0;

  // clearing display
  for(int i = 0; i < 2048; i++)
  {
    display[i] = 0;
  }
  
  // load font into memory
  load_font();  
}

void Chip8::load_rom(std::string const& path)
{
  std::ifstream rom(path, std::ios::in | std::ios::binary);
  std::vector<uint8_t>buffer((std::istreambuf_iterator<char>(rom)), std::istreambuf_iterator<char>());
  std::copy(buffer.begin(), buffer.end(), memory.begin() + 512);
}

void Chip8::cycle(sdl2::Window *w, sdl2::Renderer *r, sdl2::Texture *t) 
{
  // read 2 bytes in big endian and add pc by 1
  u_int16_t opcode = memory[pc] << 8 | memory[pc + 1];
  pc += 2;

  // Fetch opcodes by type
  u_int8_t x = (opcode >> 8) & 0x0F;
  u_int8_t y = (opcode >> 4) & 0x0F;
  u_int8_t n = opcode & 0x0F;
  u_int16_t nnn = opcode & 0x0FFF;
  u_int8_t kk = opcode & 0x0FF;

  // Opcodes
  switch(opcode & 0xF000)
  {
    case(0x0000):
      if(opcode == 0x00E0) { // clear screen
        for(int i = 0; i < 2048; i++)
        {
          display[i] = 0;
        }
        draw_flag = true;
      break;

      } else if(opcode == 0x00EE){  // return from subroutine
          pc = stack[--sp];
        }
      break;
    case(0x1000): // jump
      pc = nnn;
      break;
    case(0x3000): // skip if V[x] == kk
      if(V[x] == kk) 
        pc += 2;
      break;
    case(0x4000):
      if(V[x] != kk) // skip if V[x] != kk
        pc += 2;
      break;
    case(0x5000):
      if(V[x] == V[y]) // skip if V[x] == V[y]
        pc += 2;
        break;
    case(0x2000): // call subroutine at mem location nnn
      stack[sp++] = pc;
      pc = nnn;
      break; 
    case(0x6000): // set register vx
      V[x] = kk;
      break;
    case(0x7000): // add value to register vx
      V[x] += kk;
      break;
    case(0x8000):
      switch(opcode & 0x000F) {
        case(0x0000):
          V[x] = V[y]; 
          break;
        case(0x0001):
         V[x] = V[x] | V[y];
         break;
        case(0x0002):
          V[x] = V[x] & V[y];
          break;
        case(0x0003):
          V[x] = V[x] ^ V[y];
          break;
        case(0x0004):
          uint16_t result;
          result = V[x] + V[y];
          if(result > 255) {
            V[0xF] = 1;
          } else {
            V[0xF] = 0;
          }
          V[x] += V[y];
          break;
        case(0x0005):
          if(V[x] > V[y]) {
            V[0xF] = 1;
          } else {
            V[0xF] = 0;
          }
          V[x] = V[x] - V[y];
          break;
        case(0x0006):
          V[0xF] = V[x] & 0x1;
          V[x] >>= 1;
          break;
        case(0x0007):
          if(V[x] > V[y]) {
            V[0xF] = 0;
          } else {
            V[0xF] = 1;
          }
          V[x] = V[y] - V[x];
          break;
        case(0x000E):
          V[0xF] = V[x] >> 7;
          V[x] <<= 1;
          break;
      }
    break;
    case(0x9000):
      if(V[x] != V[y])
        pc += 2;
        break;
    case(0xA000): // set index to register I
      I = nnn;
      break;
    case(0xB000):
      pc = nnn + V[0];
      break;
    case(0xC000):
      V[x] = (rand() % (0xFF + 1)) & kk;
      break;
    case(0xD000): // draw pixel at specified x, y location`
      V[15] = 0;

      for(int i = 0; i < n; i++) {
        for(int j = 0; j < 8; j++) {
          u_int8_t pixel = (memory[I + i] & (0x80 >> j)) != 0;
          if(pixel) {
            int index = 
              (V[x] + j) % 64 +
              ((V[y] + i) % 32) * 64;
            if(pixels[index] == 0xFFFFFFFF) {
              V[15] = 1;
              pixels[index] = 0xFF000000;
            } else {
              pixels[index] = 0xFFFFFFFF;
            }
            r->draw(w->get_window(), t->get_texture(), pixels);
          }
        }
      }
        break;
    case(0xE000):
      switch(opcode & 0x00FF) {
        break;
      }
    case(0xF000):
      switch(opcode & 0x00FF) {
        case(0x0007):
          V[x] = delay_timer;
          break;
        case(0x0015):
          delay_timer = V[x];
          break;
        case(0x001E):
          V[I] = V[I] + V[x];
          break;
        case(0x0029):
          V[I] = V[x] * 0x5;
          break;
        case(0x0033):
          V[I] = V[x] / 100;
          V[I + 1] = (V[x] / 10) % 10;
          V[I + 2] = V[x] % 10;
          break;
        case(0x0055):
          for(int i = 0; i <= V[x]; i++)
            memory[I + i] = V[i];
          break;
        case(0x0065):
          for(int i = 0; i <= V[x]; i++)
            V[i] = memory[I + i];
          I = I + V[x] + 1;
          break;
      }
    break;
  }
  if(delay_timer > 0)
    --delay_timer;
}

// destructor
Chip8::~Chip8() 
{

}
