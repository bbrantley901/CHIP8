#include "chip8.h"

/* KEY
* NNN: Address
* NN: 8-bit constant
* N: 4-bit constant
* X and Y: 4-bit register identifier
* PC: Program Counter
* I: 12-bit register (for memory address)
* VN: One of the 16 available registers
*/

void Chip8::opcode0NNN()
{
  //wiki says calls a code routine at NNN 
  return; // no working implementation atm
}

void Chip8::opcode00E0()
{
  screen.ClearScreen();
}

void Chip8::opcode00EE()
{
  //return from subroutine;
}

void Chip8::opcode1NNN()
{
  // Jump to NNN
  pc = opcode & 0x0FFF;
}

void Chip8::opcode2NNN()
{
  //calls subroutine at NNN address
}

void Chip8::opcode3XNN()
{
  //skip next instruction if VX == NN
  uint8_t registerX = (opcode & 0x0F00) >> 8;
  uint8_t num = opcode & 0x00FF;
  if(registers[registerX] == num)
  {
    pc += WORD_SIZE;
  }
  
}

void Chip8::opcode4XNN()
{
  //Skip next instruction if VX != NN
  uint8_t registerX = (opcode & 0x0F00) >> 8;
  uint8_t num = opcode & 0x00FF;
  if(registers[registerX] != num)
  {
    pc += WORD_SIZE;
  }
}

void Chip8::opcode5XYO()
{
  //Skip next instruction if VX == VY
  uint8_t registerX = (opcode & 0x0F00) >> 8;
  uint8_t registerY = (opcode * 0x00F0) >> 4;
  if(registers[registerX] == registers[registerY])
  {
    pc += WORD_SIZE;
  }
}

void Chip8::opcode6XNN()
{
  //Set VX == NN
  uint8_t registerNum = opcode & 0x0F00;
  registerNum = registerNum >> 8;
  registers[registerNum] = opcode & 0x00FF;
}

void Chip8::opcode7XNN()
{
  //Add NN to VX (carry flag is not changed)
  uint8_t registerNum = opcode & 0x0F00;
  registerNum = registerNum >> 8;
  registers[registerNum] += opcode & 0x00FF;
}

void Chip8::opcode8XY0()
{
  // Set VX = VY
  uint8_t registerX = (opcode & 0x0F00) >> 8;
  uint8_t registerY = (opcode * 0x00F0) >> 4;
  registers[registerX] = registers[registerY];

}

void Chip8::opcode8XY1()
{
  // VX = VX | VY;
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode * 0x00F0) >> 4;
  registers[X] = registers[X] | registers[Y];
}

void Chip8::opcode8XY2()
{
  //VX = VX & VY
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode * 0x00F0) >> 4;
  registers[X] = registers[X] & registers[Y];
}

void Chip8::opcode8XY3()
{
  // VX = VX ^ VY
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode * 0x00F0) >> 4;
  registers[X] = registers[X] ^ registers[Y];
}

void Chip8::opcode8XY4()
{
  //VX = VX + VY
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode * 0x00F0) >> 4;
  uint16_t sum = registers[X] += registers[Y];
  if(sum > 255)
  {
    registers[0x000F] = 1;
  }
  else
  {
    registers[0x000F] = 0;
  }
  registers[X] += registers[Y];
}

void Chip8::opcode8XY5()
{
  //VX = VX - VY;
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode * 0x00F0) >> 4;
  uint16_t difference = registers[X] += registers[Y];
  if(difference < 0)
  {
    registers[0x000F] = 0;
  }
  else
  {
    registers[0x000F] = 1;
  }
}

void Chip8::opcode8XY6()
{
  //VX >>= 1
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t LSB = registers[X] & 0x0001;
  registers[0x000F] = LSB;
  registers[X] == registers[X] >> 1;
}

void Chip8::opcode8XY7()
{
  // VX = VY - VX
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode * 0x00F0) >> 4;
  int16_t difference = registers[Y] - registers[X];
  if(difference < 0)
  {
    registers[0x000F] = 0;
  }
  else
  {
    registers[0x000F] = 1;
  }
  registers[X] = registers[Y] - registers[X];
}

void Chip8::opcode8XYE()
{
  // VX <<= 1;
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t MSB = (registers[X] & 0x8000) >> 31;
  registers[0x000F] = MSB;
  registers[X] = registers[X] << 1;
}

void Chip8::opcode9XY0()
{

}

void Chip8::opcodeANNN()
{
  //Set I register to NNN
  I = opcode & 0x0FFF;
}

void Chip8::opcodeBNNN()
{

}

void Chip8::opcodeCXNN()
{

}

void Chip8::opcodeDXYN()
{
  //Draw command. Gonna be a big one...
  //come back to it tomorrow or som
  uint8_t registerX = ((opcode & 0x0F00) >> 8);
  uint8_t registerY = ((opcode & 0x00F0) >> 4);
  uint8_t xCoordinate = registers[registerX] % 64;
  uint8_t yCoordinate = registers[registerY] % 31;
  registers[0x000F] = 0;
  uint8_t nValue = 0x000F;
  for(uint8_t i = 0; i < nValue; i++)
  {
    uint8_t spriteData = memory[I + i];
    for(uint8_t j = 0; j < 8; j++)
    {
      
      if(screenData[i][j] = screenData[xCoordinate][yCoordinate])
      {

      }
    }
  }

}

void Chip8::opcodeEX9E()
{

}

void Chip8::opcodeEXA1()
{

}

void Chip8::opcodeFX07()
{

}

void Chip8::opcodeFX0A()
{

}

void Chip8::opcodeFX15()
{

}

void Chip8::opcodeFX18()
{

}

void Chip8::opcodeFX1E()
{

}

void Chip8::opcodeFX29()
{

}

void Chip8::opcodeFX33()
{

}

void Chip8::opcodeFX55()
{

}

void Chip8::opcodeFX65()
{

}