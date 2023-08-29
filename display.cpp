#include "display.h"

using namespace sdl2;
 
// window 
  Window::Window() 
    {
      window = SDL_CreateWindow("chip-8",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, 
                                 WIDTH * SCALE, 
                                 HEIGHT * SCALE, 
                                 SDL_WINDOW_SHOWN);
      if(window == nullptr)
        throw std::runtime_error("Unable to create window\n");  
    }
  Window::~Window() {SDL_DestroyWindow(window);}

// application
  Application::Application() {
      if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      {
        throw std::runtime_error("Unable to initialize SDL");
      }
    }
     
  Application::~Application() {
      SDL_Quit();
    }

// renderer
  Renderer::Renderer(SDL_Window* window){
      renderer = SDL_CreateRenderer(window,
                                     -1,                                  
                                     SDL_RENDERER_ACCELERATED);
      SDL_RenderSetScale(renderer,
                         SCALE, 
                         SCALE);
}

void Renderer::draw(SDL_Texture* texture, uint32_t pixels[WIDTH*SCALE]) {
      SDL_UpdateTexture(texture,
                        NULL,
                        pixels,
                        WIDTH*sizeof(uint32_t));
      SDL_RenderCopy(renderer,
                     texture,
                     NULL,
                     NULL);
      SDL_RenderPresent(renderer);
    }


  Renderer::~Renderer(){
      SDL_DestroyRenderer(renderer);
    }

// texture
  Texture::Texture(SDL_Renderer* renderer){
    texture = SDL_CreateTexture(renderer,
                                 SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING, 64, 32);
    }



