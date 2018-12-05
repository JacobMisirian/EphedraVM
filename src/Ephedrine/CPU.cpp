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
      case Lb:
         registers[operand1] = ram[registers[operand2]];
         break;
      case Lbi:
         registers[operand1] = ram[immediate];
         break;
      case Li:
         registers[operand1] = immediate;
         break;
      case Lw:
         registers[operand1] = (uint16_t)*(ram + registers[operand2]);
         break;
      case Lwi:
         registers[operand1] = (uint16_t)*(ram + immediate);
         break;
      case Mov:
         registers[operand1] = registers[operand2];
         break;
      case Pop:
         registers[operand1] = (uint16_t)*(ram + STACK_REGISTER);
         STACK_REGISTER += 2;
         break;
      case Push:
         STACK_REGISTER -= 2;
         *((uint16_t*)ram[STACK_REGISTER]) = registers[operand1];
         break;
      case Sb:
         ram[registers[operand1]] = registers[operand2];
         break;
      case Sbi:
         ram[registers[operand1]] = immediate;
         break;
      case Sw:
         *((uint16_t*)ram[registers[operand1]]) = registers[operand2];
         break;
      case Swi:
         *((uint16_t*)ram[registers[operand1]]) = immediate;
         break;
      case Sub:
         registers[operand1] -= registers[operand2];
         break;
      case Subi:
         registers[operand1] -= immediate;
         break;
      }
      IP_REGISTER += INSTRUCTION_SIZE;
   }

}