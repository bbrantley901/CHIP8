#include "chip8.h"
#include "stdlib.h"
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

//WORKING
void Chip8::opcode00E0()
{
  screen.ClearScreen();
}

void Chip8::opcode00EE()
{
  //return from subroutine;
  pc = stack.top();
  stack.pop();
}

//WORKING
void Chip8::opcode1NNN()
{
  // Jump to NNN
  pc = opcode & 0x0FFF;
}

void Chip8::opcode2NNN()
{
  //calls subroutine at NNN address
  stack.push(pc);
  pc = (opcode & 0x0FFF);
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

//WORKING
void Chip8::opcode6XNN()
{
  //Set VX == NN
  uint16_t registerNum = opcode & 0x0F00;
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
  uint16_t sum = registers[X] + registers[Y];
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
  registers[X] = registers[X] >> 1;
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
  // If (VX != VY) Skip next instruction
  uint8_t VX = (opcode & 0x0F00) >> 8;
  uint8_t VY = (opcode & 0x00F0) >> 4;
  if(VX != VY)
  {
    pc += WORD_SIZE; //Maybe make this a skip instruction
  }
}

//WORKING
void Chip8::opcodeANNN()
{
  //Set I register to NNN
  I = opcode & 0x0FFF;
}

void Chip8::opcodeBNNN()
{
  // Set pc to V0 + NNN
  uint16_t NNN = (opcode & 0x0FFF);
  pc = registers[0x0] + NNN;
}

void Chip8::opcodeCXNN()
{
  //Vx = rand() & NN
  //oops need to implement rand(). Come back to this   
  uint16_t range = 256;
  uint8_t num = rand() % range;
  uint8_t VX = (opcode & 0x0F00) >> 8;
  uint8_t NN = (opcode & 0x00FF);
  registers[VX] = num & NN;
}

//WORKING (I think?)
void Chip8::opcodeDXYN()
{
  // This needs a fair bit of refactoring for readability lul
  // That's an issue for later
  //Also the current screen implementation is not set up for this.
  std::cout << "Opcode is " << (int)opcode << std::endl;
  uint8_t registerX = ((opcode & 0x0F00U) >> 8U);
  uint8_t registerY = ((opcode & 0x00F0U) >> 4U);
  uint8_t xCoordinate = registers[registerX] % 64;
  std::cout << "xPos is " << (int)xCoordinate << std::endl;
  uint8_t yCoordinate = registers[registerY] % 32;
  std::cout << "yPos is " << (int)yCoordinate << std::endl;
  registers[0x000F] = 0;
  uint8_t height = opcode & 0x000F;
  for(uint8_t i = 0; i < height; i++)
  {
    uint8_t spriteData = memory[I + i];
    for(uint8_t j = 0; j < 8; j++)
    {
     
      //spriteData = (spriteData & 0x80) >> j; //mask the MSB of the sprite info
      uint8_t spritePixel = spriteData & (0x80  >> j);
      uint8_t* screenPixel = &screenData[xCoordinate + j][yCoordinate + i];
      if (spritePixel)
      {
        if(*screenPixel == 0xFF)
        {
          registers[0xF] = 1;
        }
        //screenData[i + xCoordinate][j + yCoordinate] ^= 0xFF;
        *screenPixel ^= 0xFF;
      }
      //screen.screenArray[i + xCoordinate][j + yCoordinate] = screenData[i + xCoordinate][j + yCoordinate];
      //screen.screenArray[xCoordinate + i][yCoordinate + j] = *screenPixel;   
      //printf("Pixel %d, %d is %d", yCoordinate+i, xCoordinate+j, screenData[yCoordinate+i][xCoordinate+j]); 
      std::cout << "Pixel " << xCoordinate + j << ", " << yCoordinate+i << " is " << (int)screenData[xCoordinate+j][yCoordinate+i] << std::endl;  
    }
    
  }
  memcpy(screen.screenArray, screenData,sizeof(screenData));
}

void Chip8::opcodeEX9E()
{
  //if(key() == Vx) skip next instruction
  //I need to have the keyboard part made for this
  uint8_t VX = (opcode & 0x0F00) >> 8;
  SDLkeyboard.getKeys(keyboard);
  BYTE key = registers[VX];
  if(keyboard[key])
  {
    pc += WORD_SIZE;
  }
}

void Chip8::opcodeEXA1()
{
  //if(key() != Vx) skip next instruction
  uint8_t VX = (opcode & 0x0F00) >> 8;
  SDLkeyboard.getKeys(keyboard);
  BYTE key = registers[VX];
  if(!keyboard[key])
  {
    pc += WORD_SIZE;
  }

}

void Chip8::opcodeFX07()
{
  uint8_t VX = (opcode & 0x0F00) >> 8;
  registers[VX] = delayTimer;
}

void Chip8::opcodeFX0A()
{
  uint8_t VX = (opcode & 0x0F00) >> 8;
  //Get key press
  //This current method is so awful, I swear I'll redo it at some point lmao      
  //Big case of unclear data ownership
  registers[VX] = soundTimer;
  SDLkeyboard.getKeys(keyboard);
  if(keyboard[0])
  {
    registers[VX] = 0;
  }
  else if(keyboard[1])
  {
    registers[VX] = 1;
  }
  else if(keyboard[2]) 
  {
    registers[VX] = 2;
  }
  else if(keyboard[3]) 
  {
    registers[VX] = 3;
  }
  else if(keyboard[4]) 
  {
    registers[VX] = 4;
  }
  else if(keyboard[5]) 
  {
    registers[VX] = 5;
  }
  else if(keyboard[6]) 
  {
    registers[VX] = 6;
  }
  else if(keyboard[7]) 
  {
    registers[VX] = 7;
  }
  else if(keyboard[8]) 
  {
    registers[VX] = 8;
  }
  else if(keyboard[9]) 
  {
    registers[VX] = 9;
  }
  else if(keyboard[10]) 
  {
    registers[VX] = 10;
  }
  else if(keyboard[11]) 
  {
    registers[VX] = 11;
  }
  else if(keyboard[12]) 
  {
    registers[VX] = 12;
  }
  else if(keyboard[13]) 
  {
    registers[VX] = 13;
  }
  else if(keyboard[14]) 
  {
    registers[VX] = 14;
  }
  else if(keyboard[15]) 
  {
    registers[VX] = 15;
  }
  else{
    pc -= WORD_SIZE;
 }
}

void Chip8::opcodeFX15()
{
  uint8_t VX = (opcode & 0x0F00) >> 8;
  delayTimer = registers[VX];
}

void Chip8::opcodeFX18()
{
  uint8_t VX = (opcode & 0x0F00) >> 8;
  soundTimer = registers[VX];
}

void Chip8::opcodeFX1E()
{
  // I += Vx
 uint8_t VX = (opcode & 0x0F00) >> 8;
 I += registers[VX];
}

void Chip8::opcodeFX29()
{
  // I = address of hexadecimal character in VX
  uint8_t VX = (opcode & 0x0F00) >> 8;
  uint8_t value = registers[VX];
  I = FONTSET_START_ADDRESS + (5 * value);

}

void Chip8::opcodeFX33()
{
  //store the bcd representation of VX in I
  //uhhhhhhhh refactor pls 
  uint8_t VX = (opcode & 0x0F00) >> 8;
  uint8_t value = registers[VX];
  uint8_t digit1 = value / 100;
  value -= (digit1 * 100);
  uint8_t digit2 = value / 10;
  value -= (digit2 * 10);
  uint8_t digit3 = value;
  WORD* ptrI = &I;
  *ptrI = digit1;
  *(ptrI + 1) = digit2;
  *(ptrI + 2) = digit3; 
}

void Chip8::opcodeFX55()
{
  uint8_t X = (opcode & 0x0F00) >> 8;
  WORD* ptrI = &I;
  for(WORD i = 0; i <= X; i++)
  {
    *(ptrI + i) = registers[i];
  }
}

void Chip8::opcodeFX65()
{
    uint8_t X = (opcode & 0x0F00) >> 8;
  WORD* ptrI = &I;
  for(WORD i = 0; i <= X; i++)
  {
    registers[i] = *(ptrI + i);
  }
}