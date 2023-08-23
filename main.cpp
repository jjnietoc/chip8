#include <iostream>
#include "chip8.h"
#include "display.h"
#include <stdexcept>

int main() {
  try {
    // create new chip8 object
    Chip8 chip8; 
    chip8.init();   
    chip8.load_rom("Zero Demo [zeroZshadow, 2007].ch8");

    // create all sdl2 instances
    sdl2::Application app;
    sdl2::Window window(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64*10, 32*10);
    sdl2::Renderer renderer(window.get_window());
    sdl2::Texture texture(renderer.get_renderer());
    SDL_RenderSetScale(renderer.get_renderer(), 10, 10);
    sdl2::Events events;
    
    // main loop
    bool running = true;
    Uint32 start;
    while(running) {
      start = SDL_GetTicks();
      SDL_Event event;
      if(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
          break;
        }
      }
      chip8.cycle(&window, &events, &renderer, &texture);
    }
  }

  catch(std::exception const &e) {
    std::cerr << e.what() << "\n";
  }
  
}
