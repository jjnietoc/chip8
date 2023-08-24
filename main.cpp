#include <iostream>
#include <chrono>
#include <thread>
#include "chip8.h"
#include "display.h"
#include <stdexcept>

int main() {
  try {
    // create new chip8 object
    Chip8 chip8; 
    chip8.load_rom("roms/Maze (alt) [David Winter, 199x].ch8");

    // create all sdl2 instances
    sdl2::Application app;
    sdl2::Window window;
    sdl2::Renderer renderer(window.get_window());
    sdl2::Texture texture(renderer.get_renderer());
    
    // main loop
    bool running = true;
    Uint32 start;
    while(running) {
      start = SDL_GetTicks();
      SDL_Event event;
      if(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) 
          exit(0);
        if(event.type == SDL_KEYDOWN) {
          for(int i = 0; i < SIZE; i++)
            if(event.key.keysym.sym == chip8.keymap[i]) {
              chip8.keypad[i] = 1;
              }
          }
        if(event.type == SDL_KEYUP) {
          for(int i = 0; i < SIZE; i++)
            if(event.key.keysym.sym == chip8.keymap[i]) {
              chip8.keypad[i] = 0;
            }
        }
        //  chip8.press_key(event);
      //  if(event.type == SDL_KEYUP) 
        //  chip8.release_key(event);
          
        }
      chip8.cycle(&renderer, &texture);

      std::this_thread::sleep_for(std::chrono::microseconds(1200));
    }
  }

  catch(std::exception const &e) {
    std::cerr << e.what() << "\n";
  }
  
}
