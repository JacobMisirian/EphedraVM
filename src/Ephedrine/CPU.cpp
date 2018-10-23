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
}

CPU::~CPU() {
   delete ram;
}

void CPU::execute() {
   IP_REGISTER = 0;
   while (true) {
      read_instruction(ram, IP_REGISTER, &opcode, &operand1, &operand2, &immediate);
      printf("%d\t%d\t%d\t%d\t\t%d\n", opcode, operand1, operand2, immediate, IP_REGISTER);

      switch (opcode) {
      case Add:
         registers[operand1] += registers[operand2];
         break;
      case Addi:
         registers[operand1] += immediate;
         break;
      case Hcf:
         for (int i = 0; i < 0xF; i++)
            printf("Register %d: %d\n", i, registers[i]);
         return;
      case Jmp:
         IP_REGISTER = immediate;
         continue;
      case Li:
         registers[operand1] = immediate;
         break;
      case Mov:
         registers[operand1] = registers[operand2];
         break;
      }
      IP_REGISTER += INSTRUCTION_SIZE;
   }

}