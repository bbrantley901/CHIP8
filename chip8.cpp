#include "types.h"
#include "opcodes.h"
#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

static const uint8_t WORD_SIZE = 2;
static BYTE gameMemory[0xFFF];
BYTE registers[16];
WORD addressI;
WORD programCounter;
std::stack<BYTE> stack;
BYTE screenData[64][32];

void CPU_Reset()
{
  addressI = 0;
  programCounter = 0x200;
  memset(registers, 0, sizeof(registers));
  /* File loading */
   FILE *in;
   in = fopen( "game.txt", "rb" );
   fread( &gameMemory[0x200], 0xfff, 1, in);
   fclose(in);

  return;
}

WORD getNextOpcode()
{
  WORD res = 0;
  res = gameMemory[programCounter];
  res == res << 8;
  res |= gameMemory[programCounter+1];
  programCounter += WORD_SIZE;
}

WORD decodeOPC()
{
  WORD opcode = getNextOpcode();
  WORD firstNumber = opcode & 0xF000;
  WORD secondNumber = opcode & 0x0F00;
  WORD secondAndLast = opcode & 0x0F0F;
  WORD lastTwoNumbers = opcode & 0x00FF;

  switch(firstNumber)
  {
    case 0x0000: 
      switch(opcode & 0x000F)
      {
        case 0x0000:
          opcode00E0(opcode);
          break;
        case 0x000E:
          opcode00EE(opcode);
          break;
      }
    case 0x1000:
      
    case 0x2000:

    case 0x3000:
    
    case 0x4000:

    case 0x5000:

    case 0x6000:

    case 0x7000:

    case 0x8000:

    case 0x9000:

    case 0xA000:

    case 0xB000:

    case 0xC000:

    case 0xD000:

    case 0xE000:

    case 0xF000:

    default:
      return;
  }
}
int main()
{
  CPU_Reset();
  for(auto x: gameMemory)
  {
    std::cout << x;
  }
}


