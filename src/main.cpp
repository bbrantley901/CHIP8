#include "chip8.h"
#include <iostream>
#include <cstring>
#include <chrono>
int main(int argc, char *argv[])
{
  Chip8 chip;
  
  chip.CPU_Init();
  chip.loadROM("2-ibm-logo.ch8");
  //std::cout.setf(std::ios::hex, std::ios::basefield);
  for(auto x: chip.memory)
  {
     std::cout << (int)x;
  }

/* I just copied this and need to actually figure out what it does */
  auto lastCycleTime = std::chrono::high_resolution_clock::now();
  for(;;){
    auto currentTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
    if(dt > 400)
    {
      lastCycleTime = currentTime;
      chip.Cycle();
      chip.screen.RenderWindow();
    }
  }
  return 0;
}