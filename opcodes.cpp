#include "types.h"
#include "opcodes.h"

/* Just realized this file needs access to all the CHIP8 variables lol. 
   Passing those in would be a mess so lets def turn CHIP8 into a class
  This entire thing is now deprecated
*/

/* KEY
* NNN: Address
* NN: 8-bit constant
* N: 4-bit constant
* X and Y: 4-bit register identifier
* PC: Program Counter
* I: 12-bit register (for memory address)
* VN: One of the 16 available registers
*/

void opcode0NNN(WORD opcode)
{
  //wiki says calls a code routine at NNN 
  return; // no working implementation atm
}

void opcode00E0(WORD opcode)
{
  //clear the display
}

void opcode00EE(WORD opcode)
{
  //return from subroutine;
}

void opcode1NNN(WORD opcode)
{
  //program counter jumps to NNN address
}

void opcode2NNN(WORD opcode)
{
  //calls subroutine at NNN address
}

void opcode3XNN(WORD opcode)
{
  //skip next instruction if VX == NN
}

void opcode4XNN(WORD opcode)
{
  //Skip next instruction if VX != NN
}

void opcode5XYO(WORD opcode)
{
  //Skip next instruction if VX == VY
}

void opcode6XNN(WORD opcode)
{
  //Set VX == NN
}

void opcode7XNN(WORD opcode)
{
  //Add NN to VX (carry flag is not changed)
}

void opcode8XY0(WORD opcode)
{

}

void opcode8XY1(WORD opcode)
{

}

void opcode8XY2(WORD opcode)
{

}

void opcode8XY3(WORD opcode)
{

}

void opcode8XY4(WORD opcode)
{

}

void opcode8XY5(WORD opcode)
{

}

void opcode8XY6(WORD opcode)
{

}

void opcode8XY7(WORD opcode)
{

}

void opcode8XYE(WORD opcode)
{

}

void opcode9XY0(WORD opcode)
{

}

void opcodeANNN(WORD opcode)
{

}

void opcodeBNNN(WORD opcode)
{

}

void opcodeCXNN(WORD opcode)
{

}

void opcodeDXYN(WORD opcode)
{

}

void opcodeEX9E(WORD opcode)
{

}

void opcodeEXA1(WORD opcode)
{

}

void opcodeFX07(WORD opcode)
{

}

void opcodeFX0A(WORD opcode)
{

}

void opcodeFX15(WORD opcode)
{

}

void opcodeFX18(WORD opcode)
{

}

void opcodeFX1E(WORD opcode)
{

}

void opcodeFX29(WORD opcode)
{

}

void opcodeFX33(WORD opcode)
{

}

void opcodeFX55(WORD opcode)
{

}

void opcodeFX65(WORD opcode)
{

}