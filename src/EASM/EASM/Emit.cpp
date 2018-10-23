#include "Emit.h"

Emit::Emit(std::vector<Token*> * tokens, std::ofstream * os) {
   Emit::tokens = tokens;
   Emit::os = os;
}

Emit::~Emit() {
}

void Emit::assemble() {
   for (int tok_index = 0; tok_index < tokens->size(); tok_index++) {
      TokenType token_type = (*tokens)[tok_index]->tokenType();
      std::string token_val = *(*tokens)[tok_index]->value();

      if (token_type == String)
         (*os) << token_val;
      else if (token_type == LabelDeclaration)
         label_positions[token_val] = (uint16_t)os->tellp();
      else if (token_type == Instruction)
      {
         uint8_t opcode = get_instruction_code(&token_val);
         uint8_t operand1 = 0, operand2 = 0;
         uint16_t immediate = 0;

         if (token_val == "add" || token_val == "mov") {
            operand1 = expect_register(&tok_index);
            expect_comma(&tok_index);
            operand2 = expect_register(&tok_index);
         }
         else if (token_val == "addi" || token_val == "li") {
            operand1 = expect_register(&tok_index);
            expect_comma(&tok_index);
            immediate = expect_immediate(&tok_index);
         }
         else if (token_val == "jmp")
            immediate = expect_immediate(&tok_index);
         serialize_inst(opcode, operand1, operand2, immediate);
      }
   }
}