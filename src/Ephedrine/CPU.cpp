#include "CPU.h"
#include "Instruction.h"
#include "Register.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdint.h>

CPU::CPU(size_t ram_size, std::ifstream * os) {
   ram = (char *) malloc(ram_size);
   
   os->seekg(0, std::ios::end);
   size_t os_size = (size_t)os->tellg();
   os->seekg(0, std::ios::beg);
   os->read(ram, os_size);
   os->close();
}


CPU::~CPU() {
   delete ram;
}

void CPU::execute() {
   IP_REGISTER = 0;
   for (; ; IP_REGISTER += INSTRUCTION_SIZE) {
      read_instruction(ram, IP_REGISTER, &opcode, &operand1, &operand2, &immediate);
      printf("%d\t%d\t%d\t%d\n", opcode, operand1, operand2, immediate);
      switch (opcode) {
      case Add:
         registers[operand1] += registers[operand2];
         break;
      case Addi:
         registers[operand1] += immediate;
         break;
      case Hcf:
         return;
      case Li:
         registers[operand1] = immediate;
         break;
      case Mov:
         registers[operand1] = registers[operand2];
         break;
      }
   }
}