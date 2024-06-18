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
  //clear the display
}

void Chip8::opcode00EE()
{
  //return from subroutine;
}

void Chip8::opcode1NNN()
{
  //program counter jumps to NNN address
}

void Chip8::opcode2NNN()
{
  //calls subroutine at NNN address
}

void Chip8::opcode3XNN()
{
  //skip next instruction if VX == NN
}

void Chip8::opcode4XNN()
{
  //Skip next instruction if VX != NN
}

void Chip8::opcode5XYO()
{
  //Skip next instruction if VX == VY
}

void Chip8::opcode6XNN()
{
  //Set VX == NN
}

void Chip8::opcode7XNN()
{
  //Add NN to VX (carry flag is not changed)
}

void Chip8::opcode8XY0()
{

}

void Chip8::opcode8XY1()
{

}

void Chip8::opcode8XY2()
{

}

void Chip8::opcode8XY3()
{

}

void Chip8::opcode8XY4()
{

}

void Chip8::opcode8XY5()
{

}

void Chip8::opcode8XY6()
{

}

void Chip8::opcode8XY7()
{

}

void Chip8::opcode8XYE()
{

}

void Chip8::opcode9XY0()
{

}

void Chip8::opcodeANNN()
{

}

void Chip8::opcodeBNNN()
{

}

void Chip8::opcodeCXNN()
{

}

void Chip8::opcodeDXYN()
{

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