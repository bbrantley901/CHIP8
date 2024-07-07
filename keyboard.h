#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL.h"

class Keyboard
{
  public:
    Keyboard();
    SDL_Event event;
    void getKeys(uint8_t* keys);
};


