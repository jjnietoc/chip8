#include <_types/_uint8_t.h>
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
  load_font();

  // clear stack
  for(int i = 0; i < SIZE; i++)
  {
    stack[i] = 0;
    V[i] = 0;
  }

  // clear display
  for(int i = 0; i < WIDTH * SCALE; i++)
  {
    display[i] = 0;
  }

}

void Chip8::load_font()
{
  for (int i = 0; i < 80; i++)
    memory[i] = font[i];
}

void Chip8::load_rom(std::string const& path)
{
  // create buffer and copy data to memory
  std::ifstream rom(path, std::ios::in | std::ios::binary);
  std::vector<uint8_t>buffer((std::istreambuf_iterator<char>(rom)), std::istreambuf_iterator<char>());
  std::copy(buffer.begin(), buffer.end(), memory.begin() + 512);
}

void Chip8::cycle(sdl2::Renderer *r, sdl2::Texture *t) 
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
        for(int i = 0; i < WIDTH * HEIGHT; i++)
        {
          display[i] = 0;
        }
      break;

      } else if(opcode == 0x00EE){  // return from subroutine
          pc = stack[--sp];
        }
      break;

    case(0x1000): // jump
      pc = nnn;
      break;

    case(0x2000): // call subroutine at mem location nnn
      stack[sp] = pc;
      sp++;
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
         V[x] |= V[y];
         break;
        case(0x0002):
          V[x] &= V[y];
          break;
        case(0x0003):
          V[x] ^= V[y];
          break;
        case(0x0004):
          uint16_t result;
          result = V[x] + V[y];
          V[x] = result & 0xFF;
          if(result >> 8) {
            V[0xF] = 1;
          } else {
            V[0xF] = 0;
          }
          break;
        case(0x0005):
          if(V[y] > V[x]) {
            V[0xF] = 0;
          } else {
            V[0xF] = 1;
          }
          V[x] -= V[y];
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
          V[0xF] = V[x] >> 15;
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
      V[x] = (std::rand() % (0xFF)) & kk;
      break;
    case(0xD000): // draw pixel at specified x, y location`
      V[15] = 0;

      for(int i = 0; i < n; i++) {
        for(int j = 0; j < 8; j++) {
          u_int8_t pixel = (memory[I + i] & (0x80 >> j)) != 0;
          if(pixel) {
            int index = 
              (V[x] + j) % WIDTH +
              ((V[y] + i) % HEIGHT) * WIDTH;
            if(pixels[index] == 0xFFFFFFFF) {
              V[0xF] = 1;
              pixels[index] = 0xFF000000;
            } else {
              pixels[index] = 0xFFFFFFFF;
            }
            r->draw(t->get_texture(), pixels);
          }
        }
      }
        break;

    case(0xF000):
      switch(opcode & 0x00FF) {
        case(0x0007):
          V[x] = delay_timer;
          break;

        case(0x0015):
          delay_timer = V[x];
          break;

        case(0x001E):
          if(I + V[x] > 0xFFF)
            V[0xF] = 1;
          else
            V[0xF] = 0;
          I += V[x];
          break;
        
        case(0x0018):
          sound_timer = V[x];
          break;

        case(0x0029):
          V[I] = V[x] * 0x5;
          break;

        case(0x0033):
          memory[I] = V[x] / 100;
          memory[I + 1] = (V[x] / 10) % 10;
          memory[I + 2] = V[x] % 10;
          break;

        case(0x0055):
          for(uint8_t i = 0; i <= x; i++)
            memory[I + i] = V[i];
          break;

        case(0x0065):
          for(uint8_t i = 0; i <= x; i++)
            V[i] = memory[I + i];
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
