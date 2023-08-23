#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <stdexcept>

const int WIDTH = 64;
const int HEIGHT = 32;
const int SCALE = 10;

namespace sdl2 {

  class Application {
  public: 
    Application();
    ~Application(); 
  };
 
  class Window {
  public: 
    Window();
    inline SDL_Window* get_window() { return window; }
    ~Window();

  private:
    SDL_Window *window;
  };

  class Renderer {
  public: 
    Renderer(SDL_Window* window);
    ~Renderer();

    inline SDL_Renderer* get_renderer() { return renderer; }
    inline void update() { SDL_RenderPresent(renderer); }
    void draw(SDL_Texture* texture, uint32_t pixels[WIDTH*SCALE]);

  private:
    SDL_Renderer *renderer;
  };

  class Texture {
  public:
    Texture(SDL_Renderer* renderer);
    inline SDL_Texture* get_texture() { return texture; }
    ~Texture(){

    }
  private:
    SDL_Texture *texture;
  };
}

#endif
