
#include <stdint.h>
#include "types.h"
#include <stack>
#include "window.h"
#include "keyboard.h"

static const uint8_t  WORD_SIZE = 2;
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
    BYTE memory[0x1000]; 
    BYTE registers[16];
    WORD I;
    WORD pc;
    std::stack<BYTE> stack;
    BYTE sp;
    BYTE delayTimer;
    BYTE soundTimer;
    BYTE keypad[16];
    BYTE screenData[64][32];
    BYTE keyboard[16];
    WORD opcode;
    Keyboard SDLkeyboard;
    Screen screen;

  /* Function Table Stuff */
    typedef void (Chip8::*func)();
    func table[0xF + 1];
    func table0[0xE + 1];
    func table8[0xE + 1];
    func tableE[0xE + 1];
    func tableF[0x65 + 1];

  /* Methods */
  Chip8();
  void CPU_Init();
  void loadROM(const char* filename);
  void fetchOpcode();
  void decodeOpcode();
  void decrementDelayTimer();
  void decrementSoundTimer();
  void Cycle();
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