#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdexcept>

static constexpr int WIDTH = 64;
static constexpr int HEIGHT = 32;
static constexpr int SCALE = 10;

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
