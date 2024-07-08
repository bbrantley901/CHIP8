#include <iostream>
#include "SDL2/SDL.h"

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