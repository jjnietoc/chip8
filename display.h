#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <stdexcept>
#include <sys/_types/_u_int32_t.h>

namespace sdl2 {

 
  class Window {
  public: 
    Window(int x, int y, int w, int h, bool full_screen = false);
    inline SDL_Window* get_window() {
      return nWindow;  
    }
    ~Window();

  private:
    SDL_Window *nWindow;
  };

  class Application {
  public: 
    Application();
     
  void delay(); 

    ~Application(); 
  };

  class Events { 
  public:
    bool handle_events();
  private:
    SDL_Event event;
  };

  class Renderer {
  public: 
    Renderer(SDL_Window* nWindow);
    inline SDL_Renderer* get_renderer() {
      return nRenderer;
    }
    inline void clear_screen(int r, int g, int b, int a) {
      SDL_SetRenderDrawColor(nRenderer, r, g, b, a);
      SDL_RenderClear(nRenderer);
    }
    inline void update() {
      SDL_RenderPresent(nRenderer);
    }

    inline void draw(SDL_Window* nWindow, SDL_Texture* nTexture, uint32_t pixels[64*32]) {
      SDL_UpdateTexture(nTexture, NULL, pixels, 64*sizeof(u_int32_t));
      SDL_RenderCopy(nRenderer, nTexture, NULL, NULL);
      SDL_RenderPresent(nRenderer);
    }

    ~Renderer();

  private:
    SDL_Renderer *nRenderer;
  };

  class Texture {
  public:
    Texture(SDL_Renderer* nRenderer);
    inline SDL_Texture* get_texture() {
      return nTexture;
  }
    ~Texture(){

    }
  private:
    SDL_Texture *nTexture;
  };
}

#endif
