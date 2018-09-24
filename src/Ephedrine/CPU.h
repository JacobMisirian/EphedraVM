#ifndef _CPU_H_
#define _CPU_H_

#include <fstream>
#include "Register.h"
#include <stdint.h>

class CPU {
private:
   char * ram;
   int16_t registers[0xF];
   uint8_t opcode;
   uint8_t operand1;
   uint8_t operand2;
   int16_t immediate;
public:
   CPU(size_t ram_size, std::ifstream * os);
   ~CPU();
   void execute();
};

#endif