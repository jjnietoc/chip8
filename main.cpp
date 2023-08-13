#include <iostream>
#include "chip8.h"

int main() {
  Chip8 chip8; 
  chip8.init();   // TODO: implement rest of features
  bool quit = false;
  while(!quit) {
    for(int i = 0; i < 10; i++)
      chip8.cycle();
  };

  return 0;
}
