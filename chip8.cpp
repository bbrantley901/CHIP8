/* Standard Library Dependencies */
#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

/* File Include Dependencies */
#include "types.h"
#include "chip8.h"

/* Method Implementations */
Chip8::Chip8()
{
  /* Fill memory to avoid reading garbage values */
  memset(memory, 0, sizeof(memory));

  /* Load fontset into memory */
  for(uint16_t i = 0; i < FONTSET_SIZE; i++)
  {
    memory[FONTSET_START_ADDRESS + i] = font[i];
  }

  /* Set up Function pointer table */
  table[0x0] = &Chip8::Table0;
  table[0x1] = &Chip8::opcode1NNN;
  table[0x2] = &Chip8::opcode2NNN;
  table[0x3] = &Chip8::opcode3XNN;
  table[0x4] = &Chip8::opcode4XNN;
  table[0x5] = &Chip8::opcode5XYO;
  table[0x6] = &Chip8::opcode6XNN;
  table[0x7] = &Chip8::opcode7XNN;
  table[0x8] = &Chip8::Table8;
  table[0x9] = &Chip8::opcode9XY0;
  table[0xA] = &Chip8::opcodeANNN;
  table[0xB] = &Chip8::opcodeBNNN;
  table[0xC] = &Chip8::opcodeCXNN;
  table[0xD] = &Chip8::opcodeDXYN;
  table[0xE] = &Chip8::TableE;
  table[0xF] = &Chip8::TableF;

  for(uint16_t i = 0; i < 0xE; i++)
  {
    table0[i] = opcodeNULL;
    table8[i] = opcodeNULL;
    tableE[i] = opcodeNULL;
  } 

  table0[0x0] = &Chip8::opcode00E0;
  table0[0xE] = &Chip8::opcode00EE;

  table8[0x0] = &Chip8::opcode8XY0;
  table8[0x1] = &Chip8::opcode8XY1;
  table8[0x2] = &Chip8::opcode8XY2;
  table8[0x3] = &Chip8::opcode8XY3;
  table8[0x4] = &Chip8::opcode8XY4;
  table8[0x5] = &Chip8::opcode8XY5;
  table8[0x6] = &Chip8::opcode8XY6;
  table8[0x7] = &Chip8::opcode8XY7;
  table8[0xE] = &Chip8::opcode8XYE;
  
  tableE[0x1] = &Chip8::opcodeEXA1;
  tableE[0xE] = &Chip8::opcodeEX9E;

  for(uint16_t i = 0; i < 0x65; i++)
  {
    tableF[i] = &Chip8::opcodeNULL;
  }

  tableF[0x07] = &Chip8::opcodeFX07;
  tableF[0x0A] = &Chip8::opcodeFX0A;
  tableF[0x15] = &Chip8::opcodeFX15;
  tableF[0x18] = &Chip8::opcodeFX18;
  tableF[0x1E] = &Chip8::opcodeFX1E;
  tableF[0x29] = &Chip8::opcodeFX29;
  tableF[0x33] = &Chip8::opcodeFX33;
  tableF[0x55] = &Chip8::opcodeFX55;
  tableF[0x65] = &Chip8::opcodeFX65;
}

void Chip8::CPU_Init()
{
  memset(registers, 0, sizeof(registers));
  memset(keyboard, 0, sizeof(keyboard));
  pc = START_ADDRESS;
  I = 0;
  return;
}

void Chip8::loadROM(const char* filename)
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  std::streampos size = file.tellg();
  char* buffer = new char[size];

  file.seekg(0, std::ios::beg);
  file.read(buffer, size);
  file.close();

  for(uint16_t i = 0; i < size; i++)
  {
    memory[START_ADDRESS + i] = buffer[i];
  }
  delete[] buffer;
  return;
}

void Chip8::Cycle()
{

}

/* DO NOT CALL MORE THAN ONCE PER CYCLE */
void Chip8::fetchOpcode()
{
  WORD result;
  result = memory[pc];
  result = result << 8;
  result |= memory[pc + 1];
  pc += WORD_SIZE; 
  opcode = result;
}

void Chip8::decodeOpcode()
{
  return ((*this).*table[opcode & 0x000F])();
}

void Chip8::Table0()
{
  ((*this).*(table0[opcode & 0x000F]))(); 
}

void Chip8::Table8()
{
  ((*this).*(table8[opcode & 0x000F]))();
}

void Chip8::TableE()
{
  ((*this).*(table8[opcode & 0x000F]))();
}

void Chip8::TableF()
{
  ((*this).*(tableF[opcode & 0x00FF]))();
}

void Chip8::opcodeNULL()
{
  return;
}

void Chip8::decrementDelayTimer()
{
  if(delayTimer > 0)
  {
    delayTimer--;
  }
  return;
}

void Chip8::decrementSoundTimer()
{
  if(soundTimer > 0)
  {
    soundTimer--;
  }
  return;
}




