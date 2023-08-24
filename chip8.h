#ifndef CHIP8_H_
#define CHIP8_H_

#include <_types/_uint8_t.h>
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
   
  
    uint8_t display[WIDTH * HEIGHT];
    uint32_t pixels[WIDTH * HEIGHT] = {};


  public:
    Chip8();  // constructor
    ~Chip8(); // destructor

    void load_font();
    void load_rom(std::string const& path);
    void cycle(sdl2::Renderer *r, sdl2::Texture *t);
    void clear_stack();
    void clear_display();

    std::array<uint8_t, SIZE> keymap; // sdl key mapping
    uint8_t keypad[SIZE]; // keypad

 };


#endif
