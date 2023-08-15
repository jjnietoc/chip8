#include <iostream>
#include "chip8.h"
#include <SDL2/SDL.h>
#include "display.h"
#include <fstream>
#include <iterator>
#include <vector>

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
  {
    memory[i] = font[i];
  }
}

void Chip8::init() 
{
  load_font();  
}

void Chip8::load_rom(std::string const& path)
{
  std::ifstream rom(path, std::ios::binary);
  std::vector<unsigned char>buffer(std::istreambuf_iterator<char>(rom), {});
  for(int i = 0; i < sizeof(buffer); i++)
    buffer[i] = memory[i + 512];
}

void Chip8::cycle(sdl2::Window w, sdl2::Events e, sdl2::Renderer r) 
{
//  load_rom("/ibm.ch8");
 
  // read 2 bytes in big endian and add pc by 1
  u_int16_t opcode = memory[pc] << 8 | memory[pc + 1];
  pc += 2;

  // Fetch opcodes by type
  u_int8_t x = (opcode >> 8) & 0x0F;
  u_int8_t y = (opcode >> 4) & 0x0F;
  u_int8_t nibble = opcode & 0x0F;
  u_int16_t nnn = opcode & 0x0FFF;
  u_int8_t kk = opcode & 0x0FF;

  // Opcodes
  switch(opcode & 0xF000)
  {
    case(0x0000):
      if(opcode == 0x00E0){ // clear screen
        r.clear_screen(0, 0, 0, 255);
        r.render();
        r.update();
      } else if(opcode == 0x00EE){  // pop last address from stack and set it to pc
          stack[sp--] = pc;
        }
    break;
    case(0x1000): // jump
      pc = nnn;
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
    case(0xA000): // set index to register I
      I = nnn;
      break;
    case(0xD000): // draw pixel at specified x, y location`
      int cor_x = V[x & 63];
      int cor_y = V[y & 31];
      r.draw(255, 255, 255, 255, cor_x, cor_y);
      r.render();
      r.update();
      
      break;
    
  }
}

// destructor
Chip8::~Chip8() 
{

}
