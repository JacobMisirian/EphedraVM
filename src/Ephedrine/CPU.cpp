#include "CPU.h"

CPU::CPU(size_t ram_size, FILE * os) {
   ram = (char*)calloc(1, ram_size);
   fseek(os, 0, SEEK_END);
   int os_length = ftell(os);
   rewind(os);
   fread(ram, os_length, 1, os);
   devices = new std::vector<Device*>();
}

CPU::~CPU() {
   delete devices;
   delete ram;
}

void CPU::execute() {
   CPU::start_devices();
   STACK_REGISTER = 1000;
   IP_REGISTER = 0;

   uint8_t opcode, operand1, operand2;
   uint16_t immediate;
   uint32_t inst;

   while (true) {
      inst = *(uint32_t*)(ram + IP_REGISTER);
      opcode = (uint8_t)(inst >> 28);
      operand1 = (uint8_t)((inst >> 16) & 63);
      operand2 = (uint8_t)((inst >> 22) & 63);
      immediate = (uint16_t)(inst & 0xFF);
      printf("Code: %d Op1: %d Op2: %d Imm: %d\n", opcode, operand1, operand2, immediate);
      printf("Inst: %u\n", inst);

      switch (opcode) {
      case Add:
         registers[operand1] += registers[operand2];
         break;
      case Addi:
         registers[operand1] += immediate;
         break;
      case Hcf:
         stop_devices();
         for (int i = 0; i < 0xF; i++)
            printf("Register %d: %d\n", i, registers[i]);
         while (true);
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
         *((uint16_t*)(ram + STACK_REGISTER)) = registers[operand1];
         break;
      case Pushi:
         STACK_REGISTER -= 2;
         *((uint16_t*)(ram + STACK_REGISTER)) = immediate;
         break;
      case Sb:
         ram[registers[operand1]] = (uint8_t)registers[operand2];
         break;
      case Sbi:
         ram[registers[operand1]] = (uint8_t)immediate;
         break;
      case Sw:
         *((uint16_t*)(ram + registers[operand1])) = registers[operand2];
         break;
      case Swi:
         *((uint16_t*)(ram + registers[operand1])) = immediate;
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

void CPU::start_devices() {
   std::vector<Device*>::iterator iter;
   for (iter = devices->begin(); iter != devices->end(); iter++) {
      (*iter)->power_on();
   }
}

void CPU::stop_devices() {
   std::vector<Device*>::iterator iter;
   for (iter = devices->begin(); iter != devices->end(); iter++) {
      (*iter)->power_off();
   }
}