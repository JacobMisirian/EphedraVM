//#define _LEXER_TESTING_

#include "Emit.h"
#include <fstream>
#include "Lexer.h"
#include <string>
#include "TokenType.h"

int main(int argc, char *argv[]) {
   const char * code = "jmp main jmp end .end hcf .main li r1, 69 addi r1, 2 mov r3, r1 jmp end";

   std::vector<Token*> tokens;
   Lexer * l = new Lexer(code, &tokens);
   l->scan();

#ifdef _LEXER_TESTING_
   for (int i = 0; i < tokens.size(); i++)
   {
      std::cout << "Type: " << tokens[i]->tokenType() << " Value: " << (*tokens[i]->value()) << std::endl;
   }
#endif

   std::ofstream os;
   os.open(argv[1], std::ios::out | std::ios::binary | std::ios::ate);
   Emit * emit = new Emit(&tokens, &os);
   emit->assemble();
   os.close();
}