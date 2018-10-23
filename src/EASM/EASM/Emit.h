#ifndef _EMIT_H_
#define _EMIT_H_

#include <fstream>
#include "InstructionInfo.h"
#include <map>
#include "RegisterInfo.h"
#include <stdint.h>
#include <string>
#include "Token.h"
#include <vector>

class Emit
{
private:
   std::vector<Token*> * tokens;
   std::map<std::string, uint16_t> label_positions;
   std::ofstream * os;

   void serialize_inst(uint8_t opcode, uint8_t operand1, uint8_t operand2, uint16_t immediate) {
      printf("Serializing %d\t%d\t%d\t%d\t\t%d\n", opcode, operand1, operand2, immediate, (uint16_t)os->tellp());
      uint32_t i = immediate;
      i ^= ((uint32_t)operand1 << 16);
      i ^= ((uint32_t)operand2 << 22);
      i ^= ((uint32_t)opcode << 28);
      std::cout << i << std::endl;
      os->write((char*)(&i), sizeof(uint32_t));
   }

   uint16_t seek_label(int tok_index, std::string * target) {
      uint16_t offset = 4;

      for (; tok_index < tokens->size(); tok_index++) {
         if (label_positions.find(*target) != label_positions.end())
            return label_positions[*target];

         TokenType token_type = (*tokens)[tok_index]->tokenType();
         std::string token_val = *(*tokens)[tok_index]->value();
         if (token_type == Instruction)
            offset += 4;
         else if (token_type == String)
            offset += token_val.length() + 1;
         else if (token_type == LabelDeclaration) {
            if (label_positions.find(token_val) == label_positions.end()) {
               uint16_t position = offset + (uint16_t)os->tellp();
               label_positions[token_val] = position;
            }
         }
      }
      return -1;
   }

   void expect_comma(int * tok_index) {
      TokenType token_type = (*tokens)[++(*tok_index)]->tokenType();
      std::string * token_val = (*tokens)[*tok_index]->value();
      if (token_type == Comma)
         return;
      else
         printf("Error expected comma, instead got %d %s\n", token_type, token_val);

   }

   uint8_t expect_register(int * tok_index) {
      if ((*tokens)[++(*tok_index)]->tokenType() == Register) {
         return get_register_code((*tokens)[*tok_index]->value());
      }
      else {
         return -1;
      }
   }

   uint16_t expect_immediate(int * tok_index) {
      TokenType token_type = (*tokens)[++(*tok_index)]->tokenType();
      std::string * token_val = (*tokens)[*tok_index]->value();
      if (token_type == LabelRequest) {
         return seek_label(*tok_index, token_val);
      }
      else if (token_type == Integer) {
         return std::stoi(*token_val);
      }
      else {
         printf("Error expected label or integer, instead got %d, %s\n", token_type, *token_val);
         return -1;
      }
   }

public:
   Emit(std::vector<Token*> * tokens, std::ofstream * os);
   ~Emit();
   void assemble();
};

#endif