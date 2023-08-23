#include "display.h"

using namespace sdl2;
 
  //  sdl2::Window window(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64*10, 32*10);

  Window::Window() 
    {
      window = SDL_CreateWindow("chip-8",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, 
                                 64 * 10, 
                                 32 * 10, 
                                 SDL_WINDOW_SHOWN);
      if(window == nullptr)
        throw std::runtime_error("Unable to create window\n");  
    }
  Window::~Window() {SDL_DestroyWindow(window);}


  Application::Application() {
      if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      {
        throw std::runtime_error("Unable to initialize SDL");
      }
    }
     
  Application::~Application() {
      SDL_Quit();
    }

  Renderer::Renderer(SDL_Window* window){
      renderer = SDL_CreateRenderer(window,
                                     -1,                                  
                                     SDL_RENDERER_ACCELERATED); 
}

  Renderer::~Renderer(){
      SDL_DestroyRenderer(renderer);
    }

  Texture::Texture(SDL_Renderer* renderer){
    texture = SDL_CreateTexture(renderer,
                                 SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING, 64, 32);
    }
