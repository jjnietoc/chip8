#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>

class Window
{
  public: 
    Window() {
      SDL_Init(SDL_INIT_VIDEO);
      SDLWindow = SDL_CreateWindow(
        "Chip8", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        500, 300,
        0
      );
      SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);
    }
  
  void RenderFrame() {
    SDL_UpdateWindowSurface(SDLWindow);
  }  
  private:
    SDL_Window * SDLWindow{ nullptr };
    SDL_Surface * SDLWindowSurface { nullptr };
};

#endif
