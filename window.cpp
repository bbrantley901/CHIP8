#include <iostream>
#include "SDL2/SDL.h"


/* To do all the drawing we need to create a window 
and use the renderer to actually draw to the screen and update it.
Wonder what issues will arise when I start calling this from the cpu instructions
*/

typedef enum{
  BLACK,
  WHITE
} PixelColor;
static const uint16_t TITLE_BAR_SIZE = 50;
typedef int status_t;
class Screen
{
  public:
    Screen();
    void UpdatePixel(uint16_t x, uint16_t y, bool state);
    void RenderWindow();
    void DestroyScreen();
    void ClearScreen();
    uint8_t screenArray[64][32];
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
  private:
    void DrawPoint(uint16_t x, uint16_t y, bool color);
};

Screen::Screen()
{
  status_t status = SDL_InitSubSystem(SDL_INIT_VIDEO);
  if(status != 0)
  {
    std::cerr << "Failed to Initialize SDL video subsystem" << std::endl;
  } 

  SDL_CreateWindowAndRenderer(2560, 1440 - TITLE_BAR_SIZE, 0, &window, &renderer);
  /* This allows us to set the programmed resolution to the same as the chip-8's */
  SDL_RenderSetLogicalSize(renderer, 64, 32);
  SDL_SetWindowTitle(window, "CHIP-8");
  memset(screenArray, 0, sizeof(screenArray));
  if(window == nullptr)
  {
    std::cerr << "Window could not be created " << std::endl;
  }
  
  if(renderer == nullptr)
  {
    std::cerr << "Renderer could not be created " << std::endl;
  }

}

void Screen::UpdatePixel(uint16_t x, uint16_t y, bool state)
{
  screenArray[x][y] = state;
}

void Screen::RenderWindow()
{
  SDL_RenderClear(renderer);
  for(uint16_t i = 0; i < 64; i++)
  {
    for(uint16_t j = 0; j < 32; j++)
    {
      DrawPoint(i, j, screenArray[i][j]);
    }
  }

  SDL_RenderPresent(renderer);
}

void Screen::ClearScreen()
{
  memset(screenArray, 0, sizeof(screenArray));
}

void Screen::DestroyScreen()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Screen::DrawPoint(uint16_t x, uint16_t y, bool color)
{
  if(color == WHITE)
  {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  else
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  }
  SDL_RenderDrawPoint(renderer, x, y);
}

int main()
{
  Screen screen;
  screen.UpdatePixel(32,16, true);
  screen.RenderWindow();
  SDL_Delay(1000);
  screen.UpdatePixel(32,14, true);
  screen.RenderWindow();
  SDL_Delay(1000);
  screen.UpdatePixel(32, 12, true);
  screen.UpdatePixel(32, 14, false);
  screen.RenderWindow();
  SDL_Delay(1000);
  screen.ClearScreen();
  screen.RenderWindow();
  SDL_Delay(1000);
  screen.DestroyScreen();
  return 0;
  
}