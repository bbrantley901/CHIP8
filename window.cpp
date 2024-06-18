#include <iostream>
#include "SDL2/SDL.h"

typedef int status_t;
class Window
{
  public:
    Window();

  private:
};

Window::Window()
{
  status_t status = SDL_InitSubSystem(SDL_INIT_VIDEO);
  if(status != 0)
  {
    std::cerr << "Failed to Initialize SDL video subsystem" << std::endl;
  } 
  SDL_Window* window = SDL_CreateWindow("screen", 0, 0, 32, 64, 0);

}