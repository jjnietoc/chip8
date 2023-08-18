#include "display.h"

using namespace sdl2;
 
  
  Window::Window(int x, int y, int w, int h, bool full_screen) 
    {
      nWindow = SDL_CreateWindow("Chip8", x, y, w , h, full_screen = false);
      if(nWindow == nullptr)
        throw std::runtime_error("Unable to create window\n");  
    }
  Window::~Window() {SDL_DestroyWindow(nWindow);}


  Application::Application() {
      if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      {
        throw std::runtime_error("Unable to initialize SDL");
      }
    }
     
  void delay() 
  {
    SDL_Delay(10000);
  }

  Application::~Application() {
      SDL_Quit();
    }

    bool Events::handle_events()
    {
      while(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT)
          return false;
      }
      return true;
    }

  Renderer::Renderer(SDL_Window* nWindow){
      nRenderer = SDL_CreateRenderer(nWindow, -1, 0);
    }

  Renderer::~Renderer(){
      SDL_DestroyRenderer(nRenderer);
    }

  Texture::Texture(SDL_Renderer* nRenderer){
    nTexture = SDL_CreateTexture(nRenderer, SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING, 64, 32);
    }
