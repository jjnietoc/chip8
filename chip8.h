#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <SDL2/SDL.h>

#include "display.h"

static constexpr int SIZE = 16;
static constexpr  int MEMSIZE = 4096;
static constexpr int FONTSIZE = 80;

class Chip8 {
  private:
    // Memory
    std::array<uint8_t, MEMSIZE> memory;

    // Registers
    uint8_t V[SIZE];

    // Stack
    uint16_t stack[SIZE];

    // Font space in memory
    std::array<uint8_t, FONTSIZE> font;
  
    // register I, program counter
    uint16_t I, pc;     

    // delay timer, sound timer, stack pointer
    uint8_t delay_timer, sound_timer, sp;     
    

    // Externals
    std::array<uint8_t, WIDTH * HEIGHT> display;  // array for window data
    uint32_t pixels[WIDTH * HEIGHT] = {};   // array for pixel manipulation


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
