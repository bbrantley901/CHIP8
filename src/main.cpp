#include "chip8.h"
#include <iostream>
#include <cstring>
#include <chrono>
int main(int argc, char *argv[])
{
  Chip8 chip;
  
  chip.CPU_Init();
  chip.loadROM("test_opcode.ch8");
  for(auto x: chip.memory)
  {
    std::cout << x;
  }

  /*
  chip.screen.UpdatePixel(32,16, true);
  chip.screen.RenderWindow();
  SDL_Delay(1000);
  chip.screen.UpdatePixel(32,14, true);
  chip.screen.RenderWindow();
  SDL_Delay(1000);
  chip.screen.UpdatePixel(32, 12, true);
  chip.screen.UpdatePixel(32, 14, false);
  chip.screen.RenderWindow();
  SDL_Delay(1000);
  chip.screen.ClearScreen();
  chip.screen.RenderWindow();
  SDL_Delay(1000);
  chip.screen.DestroyScreen();
*/
  auto lastCycleTime = std::chrono::high_resolution_clock::now();
  for(;;){
    auto currentTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
    if(dt > 200)
    {
      lastCycleTime = currentTime;
      chip.Cycle();
      chip.screen.RenderWindow();
    }
  }
  return 0;
}