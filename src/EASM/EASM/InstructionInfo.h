#ifndef _INSTRUCTION_INFO_H_
#define _INSTRUCTION_INFO_H_

#include <set>
#include <stdint.h>

static const std::set<std::string> instruction_identifiers = { "add", "addi", "hcf", "jmp", "lb", "lbi", "li", "lw", "lwi", "mov", "pop", "push", "sb", "sbi", "sw", "swi", "sub", "subi" };

static uint8_t get_instruction_code(std::string * inst) {
   auto it = find(instruction_identifiers.begin(), instruction_identifiers.end(), *inst);
   if (it != instruction_identifiers.end())
      return (uint8_t)std::distance(instruction_identifiers.begin(), it);
}

#endif