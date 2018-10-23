#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

const static int INSTRUCTION_SIZE = 4;

static void read_instruction(char * ram, int16_t offset, uint8_t * opcode, uint8_t * operand1, uint8_t * operand2, int16_t * immediate) {
   uint32_t * i = (uint32_t *)(ram + offset);

   * opcode = (*i >> 28);
   * operand1 = (*i >> 16) & 63;
   * operand2 = (*i >> 22) & 63;
   * immediate = (*i & 0x00FF);
}

enum InstructionType {
   Add,
   Addi,
   Hcf,
   Jmp,
   Lb,
   Lbi,
   Li,
   Lw,
   Lwi,
   Mov,
   Pop,
   Push,
   Sb,
   Sbi,
   Sw,
   Swi,
   Sub,
   Subi,
};

#endif