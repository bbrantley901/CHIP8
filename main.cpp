#include "chip8.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{
  Chip8 chip;
  
  chip.CPU_Init();
  chip.loadROM(filename);
  for(auto x: chip.memory)
  {
    std::cout << x;
  }
}