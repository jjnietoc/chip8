#ifndef CHIP8_H_
#define CHIP8_H_

#include "display.h"
#include <array>
#include <SDL2/SDL.h>

const int SIZE = 16;
const int MEMSIZE = 4096;
const int FONTSIZE = 80;

class Chip8 {
  private:
    // Memory
    u_int8_t memory[MEMSIZE];
    // Registers
    u_int8_t V[SIZE];
    // Stack
    u_int16_t stack[SIZE];
    // Font space in memory
     std::array<u_int8_t, FONTSIZE> font;
    

    // Parts
    u_int16_t I, pc; // register I, program counter
    u_int8_t delay_timer, sound_timer, sp; // delay timer, sound timer, stack pointer
    
    // Externals
    int keypad[16]; // keypad 

  public:
    Chip8();  // constructor
    void load_font();
    void init();

    // dissassembler and decoder functions
    // optional
    u_int16_t fetch_opcode();
    u_int8_t fetch_x();
    u_int8_t fetch_y();
    u_int8_t fetch_nibble();
    u_int16_t fetch_nnn();
    u_int8_t fetch_kk();

    // load rom
    void load_rom(std::string const& path);

    // main loop function
    void cycle(sdl2::Window w, sdl2::Events e, sdl2::Renderer r);

    ~Chip8(); // destructor
};


#endif
