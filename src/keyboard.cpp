#include "keyboard.h"

Keyboard::Keyboard()
{
  
}
void Keyboard::getKeys(uint8_t* keys)
{
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_1:
          keys[0] = 1;
          break;
        case SDLK_2: 
          keys[1] = 1;
          break;
        case SDLK_3:
          keys[2] = 1;
          break;
        case SDLK_4: 
          keys[3] = 1;
          break;
        case SDLK_q:
          keys[4] = 1;
          break;
        case SDLK_w:
          keys[5] = 1;
          break;
        case SDLK_e:
          keys[6] = 1;
          break;
        case SDLK_r: 
          keys[7] = 1;
          break;
        case SDLK_a:
          keys[8] = 1;
          break;
        case SDLK_s:
          keys[9] = 1;
          break;
        case SDLK_d:
          keys[10] = 1;
          break;
        case SDLK_f:
          keys[11] = 1;
          break;
        case SDLK_z:
          keys[12] = 1;
          break;
        case SDLK_x:
          keys[13] = 1;
          break;
        case SDLK_c:
          keys[14] = 1;
          break;
        case SDLK_v:
          keys[15] = 1;
          break;
        default:
          break;
      }
    }
    else if(event.type == SDL_KEYUP)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_1:
          keys[0] = 1;
          break;
        case SDLK_2: 
          keys[1] = 1;
          break;
        case SDLK_3:
          keys[2] = 1;
          break;
        case SDLK_4: 
          keys[3] = 1;
          break;
        case SDLK_q:
          keys[4] = 1;
          break;
        case SDLK_w:
          keys[5] = 1;
          break;
        case SDLK_e:
          keys[6] = 1;
          break;
        case SDLK_r: 
          keys[7] = 1;
          break;
        case SDLK_a:
          keys[8] = 1;
          break;
        case SDLK_s:
          keys[9] = 1;
          break;
        case SDLK_d:
          keys[10] = 1;
          break;
        case SDLK_f:
          keys[11] = 1;
          break;
        case SDLK_z:
          keys[12] = 1;
          break;
        case SDLK_x:
          keys[13] = 1;
          break;
        case SDLK_c:
          keys[14] = 1;
          break;
        case SDLK_v:
          keys[15] = 1;
          break;
        default:
          break;
      }
    }
  }
}