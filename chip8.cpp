#include "types.h"
#include "opcodes.h"
#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

// Timing should be around 700 Chip8 instructions / second
// CPU clockpeed for these processors were between 1 - 4 MHz

static const uint16_t START_ADDRESS = 0x200;
static const uint16_t FONTSET_SIZE = 80;
static const uint16_t FONTSET_START_ADDRESS = 0x50;
static const BYTE font[FONTSET_SIZE] = 
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
static const char* filename = "game.txt";
class Chip8
{
  public:
  /* CPU Information */
    BYTE memory[0xFFF]; 
    BYTE registers[16];
    WORD I;
    WORD pc;
    std::stack<BYTE> stack;
    BYTE sp;
    BYTE delayTimer;
    BYTE soundTimer;
    BYTE keypad[16];
    BYTE screenData[64][32];

  /* Function Table Stuff */
    typedef void (Chip8::*func)();
    func table[0xF + 1];
    func table0[0xE + 1];
    func table8[0xE + 1];
    func tableE[0xE + 1];
    func tableF[0x65 + 1];

  /* Methods */
  Chip8();
  void CPU_Reset();
  void loadROM(const char* filename);
  WORD fetchOpcode();
  void decodeOpcode();
  void executeInstruction();
  void opcode0NNN();
  void opcode00E0();
  void opcode00EE();
  void opcode1NNN();
  void opcode2NNN();
  void opcode3XNN();
  void opcode4XNN();
  void opcode5XYO();
  void opcode6XNN();
  void opcode7XNN();
  void opcode8XY0();
  void opcode8XY1();
  void opcode8XY2();
  void opcode8XY3();
  void opcode8XY4();
  void opcode8XY5();
  void opcode8XY6();
  void opcode8XY7();
  void opcode8XYE();
  void opcode9XY0();
  void opcodeANNN();
  void opcodeBNNN();
  void opcodeCXNN();
  void opcodeDXYN();
  void opcodeEX9E();
  void opcodeEXA1();
  void opcodeFX07();
  void opcodeFX0A();
  void opcodeFX15();
  void opcodeFX18();
  void opcodeFX1E();
  void opcodeFX29();
  void opcodeFX33();
  void opcodeFX55();
  void opcodeFX65();
  void Table0();
  void Table8();
  void TableE();
  void TableF();
  void opcodeNULL();
};
static const uint8_t WORD_SIZE = 2;
static BYTE gameMemory[0xFFF];
BYTE registers[16];
WORD addressI;
WORD programCounter;
std::stack<BYTE> stack;
BYTE screenData[64][32];

Chip8::Chip8()
{

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
void Chip8::CPU_Reset()
{
  memset(registers, 0, sizeof(registers));
  pc = START_ADDRESS;
  I = 0;
  loadROM(filename);
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
}

WORD Chip8::fetchOpcode()
{
  WORD result;
  result = memory[pc];
  result = result << 8;
  result |= memory[pc + 1];
  pc += WORD_SIZE;
  return result;
}

void Chip8::decodeOpcode()
{

}

/* Classless C implementations */
#pragma region 
/*
void CPU_Reset()
{
  addressI = 0;
  programCounter = 0x200;
  memset(registers, 0, sizeof(registers));
  // File loading 
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
  return res;
}

void decodeOPC()
{
  WORD opcode = getNextOpcode();
  WORD firstNumber = opcode & 0xF000;
  WORD secondNumber = opcode & 0x0F00;
  WORD secondAndLast = opcode & 0x0F0F;
  WORD lastTwoNumbers = opcode & 0x00FF;
  WORD lastNumber = opcode & 0x000F;
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
      break;
    case 0x1000:
      opcode1NNN(opcode);
      break;
    case 0x2000:
      opcode2NNN(opcode);
      break;
    case 0x3000:
      opcode3XNN(opcode);
    case 0x4000:
      opcode4XNN(opcode);
      break;
    case 0x5000:
      opcode5XYO(opcode);
      break;
    case 0x6000:
      opcode6XNN(opcode);
      break;
    case 0x7000:
      opcode7XNN(opcode);
      break;
    case 0x8000:
      switch(lastNumber)
      {
        case 0x0000:
          opcode8XY0(opcode);
          break;
        case 0x0001:
          opcode8XY1(opcode);
          break;
        case 0x0002:
          opcode8XY2(opcode);
          break;
        case 0x0003:
          opcode8XY3(opcode);
          break;
        case 0x0004: 
          opcode8XY4(opcode);
          break;
        case 0x0005:
          opcode8XY5(opcode);
          break;
        case 0x0006:
          opcode8XY6(opcode);
          break;
        case 0x0007:
          opcode8XY7(opcode);
          break;
        case 0x000E:
          opcode8XYE(opcode);
          break;
      }
      break;
    case 0x9000:
      opcode9XY0(opcode);
      break;
    case 0xA000:
      opcodeANNN(opcode);
      break;
    case 0xB000:
      opcodeBNNN(opcode);
      break;
    case 0xC000:
      opcodeCXNN(opcode);
      break;
    case 0xD000:
      opcodeDXYN(opcode);
      break;
    case 0xE000:
      switch(lastNumber)
      {
        case 0x0001:
          opcodeEXA1(opcode);
          break;
        case 0x000E:
          opcodeEX9E(opcode);
          break;
      }
      break;
    case 0xF000:
      switch(lastTwoNumbers)
      {
        case 0x0007:
          opcodeFX07(opcode);
          break;
        case 0x000A:
          opcodeFX0A(opcode);
          break;
        case 0x0015:
          opcodeFX15(opcode);
          break;
        case 0x0018:
          opcodeFX18(opcode);
          break;
        case 0x001E:
          opcodeFX1E(opcode);
          break;
        case 0x0029:
          opcodeFX29(opcode);
          break;
        case 0x0033:
          opcodeFX33(opcode);
          break;
        case 0x0055:
          opcodeFX55(opcode);
          break;
        case 0x0065:
          opcodeFX65(opcode);
          break;
      }
      break;
    default:
      return;
  }
}
*/

#pragma endregion

int main()
{
  Chip8 chip;
  chip.CPU_Reset();
  for(auto x: chip.memory)
  {
    std::cout << x;
  }
  /*
  CPU_Reset();
  for(auto x: gameMemory)
  {
    std::cout << x;
  }
  */
}


