#ifndef _CPU_H_
#define _CPU_H_

#include <fstream>
#include "Register.h"
#include <stdint.h>
#include <stdio.h>

class CPU {
public:
   CPU(size_t ram_size, FILE * os);
   ~CPU();
   void execute();
private:
   char * ram;
   int16_t registers[16];
   uint8_t opcode;
   uint8_t operand1;
   uint8_t operand2;
   int16_t immediate;
};

#endif