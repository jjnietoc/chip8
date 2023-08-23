#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <stdexcept>

namespace sdl2 {
 
  class Window {
  public: 
    Window();
    inline SDL_Window* get_window() {
      return window;  
    }
    ~Window();

  private:
    SDL_Window *window;
  };

  class Application {
  public: 
    Application();
    ~Application(); 
  };

  class Renderer {
  public: 
    Renderer(SDL_Window* window);
    inline SDL_Renderer* get_renderer() {
      return renderer;
    }
    inline void update() {
      SDL_RenderPresent(renderer);
    }

    inline void draw(SDL_Window* window, SDL_Texture* texture, uint32_t pixels[64*32]) {
      SDL_UpdateTexture(texture, NULL, pixels, 64*sizeof(u_int32_t));
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }

    ~Renderer();

  private:
    SDL_Renderer *renderer;
  };

  class Texture {
  public:
    Texture(SDL_Renderer* renderer);
    inline SDL_Texture* get_texture() {
      return texture;
  }
    ~Texture(){

    }
  private:
    SDL_Texture *texture;
  };
}

#endif
