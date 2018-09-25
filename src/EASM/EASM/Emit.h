#ifndef _EMIT_H_
#define _EMIT_H_

#include <fstream>
#include <stdint.h>
#include "Token.h"
#include <vector>

class Emit
{
private:
   std::vector<Token*> * tokens;
   std::map<std::string, int> labels;
   std::ofstream * os;

   void serialize_inst(uint8_t opcode, uint8_t operand1, uint8_t operand2, uint16_t immediate) {
      uint32_t i = immediate;
      i ^= ((uint32_t)operand1 << 17);
      i ^= ((uint32_t)operand2 << 23);
      i ^= ((uint32_t)opcode << 28);
      
      (*os) << i;
   }
public:
   Emit(std::vector<Token*> * tokens, std::ofstream * os);
   ~Emit();
   void assemble();
};

#endif