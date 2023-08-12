#ifndef CHIP8_H_
#define CHIP8_H_

#include <array>

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
    void graphics();
    void game_loop();

    ~Chip8(); // destructor
};


#endif
