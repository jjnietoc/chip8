#ifndef CPU_HPP_
#define CPU_HPP_

#include <array>
#include <stack>

const int SIZE = 16;
const int MAXMEM = 4096;
const int FONTSIZE = 80;

class CPU {
  private:
    u_int16_t I;  // store memory addresses
    u_int16_t  PC; // program counter
    u_int8_t DT;   // delay timer
    u_int8_t ST;   // sound timer
    u_int8_t SP; //stack pointer
    
    std::array <u_int8_t, MAXMEM> memory;   // memory
    std::array <u_int8_t, SIZE> registers; // V0 to VF, VF is carry flag
    std::array<u_int16_t, SIZE> stack; // TODO: implement stack funcs
    std::array <u_int8_t, FONTSIZE> font;
  public:
    CPU();
    void load_font();
    void init();
    void graphics();
    void game_loop();
};


#endif
