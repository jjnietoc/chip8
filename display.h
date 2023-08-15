#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL2/SDL.h>
#include <stdexcept>

namespace sdl2 {

  class Window {
  public: 
    Window(int x, int y, int w, int h, bool full_screen = false) 
    {
      nWindow = SDL_CreateWindow("", x, y, w , h, full_screen);
      if(nWindow == nullptr)
        throw std::runtime_error("Unable to create window\n");  
    }
    inline SDL_Window* get_window() {
      return nWindow;  
    }
    ~Window() {SDL_DestroyWindow(nWindow);}

  private:
    SDL_Window *nWindow;
  };

  class Application {
  public: 
    Application() {
      if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      {
        throw std::runtime_error("Unable to initialize SDL");
      }
    }
    ~Application() {
      SDL_Quit();
    }
  };

  class Events { 
  public:
    bool handle_events()
    {
      while(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT)
          return false;
      }
      return true;
    }
  private:
    SDL_Event event;
  };

  class Renderer {
  public: 
    Renderer(SDL_Window* nWindow){
      nRenderer = SDL_CreateRenderer(nWindow, -1, 0);
    }
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

    inline void draw(int r, int g, int b, int a, int x, int y) {
      SDL_SetRenderDrawColor(nRenderer, r, g, b, a);
      SDL_RenderDrawPoint(nRenderer, x, y);
    }
    void render() 
    {

    }
    ~Renderer(){
      SDL_DestroyRenderer(nRenderer);
    }
  private:
    SDL_Renderer *nRenderer;
  };
}

#endif
