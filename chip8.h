#ifndef CHIP8_H_
#define CHIP8_H_

#include <array>
#include <SDL2/SDL.h>

#include "display.h"

const int SIZE = 16;
const int MEMSIZE = 4096;
const int FONTSIZE = 80;

class Chip8 {
  private:
    // Memory
    std::array<u_int8_t, MEMSIZE> memory;

    // Registers
    u_int8_t V[SIZE];

    // Stack
    u_int16_t stack[SIZE];

    // Font space in memory
    std::array<u_int8_t, FONTSIZE> font;
  
    // register I, program counter
    u_int16_t I, pc;     
    // delay timer, sound timer, stack pointer
    u_int8_t delay_timer, sound_timer, sp;     
    

    // Externals
    int keypad[SIZE]; // keypad 
    uint8_t display[WIDTH * HEIGHT];
    uint32_t pixels[WIDTH * HEIGHT] = {};


  public:
    Chip8();  // constructor
    ~Chip8(); // destructor

    void load_font();
    void load_rom(std::string const& path);
    void cycle(sdl2::Renderer *r, sdl2::Texture *t);

    // dissassembler and decoder functions
    // optional
    u_int16_t fetch_opcode();
    u_int8_t fetch_x();
    u_int8_t fetch_y();
    u_int8_t fetch_nibble();
    u_int16_t fetch_nnn();
    u_int8_t fetch_kk();

 };


#endif
