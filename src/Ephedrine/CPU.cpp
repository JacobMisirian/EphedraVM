#include "CPU.h"
#include "Instruction.h"
#include "Register.h"

CPU::CPU(size_t ram_size, FILE * os) {
   ram = (char*)malloc(ram_size);
   fseek(os, 0, SEEK_END);
   int os_length = ftell(os);
   printf("OS Length is %d\n", os_length);
   rewind(os);
   fread(os, os_length, 1, os);
}

CPU::~CPU() {
   delete ram;
}

void CPU::execute() {
   STACK_REGISTER = 1000;
   IP_REGISTER = 0;

   uint8_t opcode, operand1, operand2;
   uint16_t immediate;
   uint32_t inst;

   while (true) {
      inst = *(uint32_t*)(ram);
      printf("INST %u\n", inst);
      opcode = (uint8_t)(inst >> 28);
      operand1 = (uint8_t)((inst >> 16) & 63);
      operand2 = (uint8_t)((inst >> 22) & 63);
      immediate = (uint16_t)(inst & 0x00FF);

      printf("Code: %d Op1: %d Op2: %d Imm: %d\n", opcode, operand1, operand2, immediate);

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