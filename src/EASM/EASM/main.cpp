//#define _LEXER_TESTING_

#include "Emit.h"
#include <fstream>
#include "Lexer.h"
#include <sstream>
#include <string>
#include "TokenType.h"

const char * code;

int main(int argc, char *argv[]) {
   std::ifstream * is = new std::ifstream(argv[1], std::ios::in);
   std::vector<Token*> tokens;
   Lexer * l = new Lexer(is, &tokens);
   l->scan();

#ifdef _LEXER_TESTING_
   for (int i = 0; i < tokens.size(); i++)
   {
      std::cout << "Type: " << tokens[i]->tokenType() << " Value: " << (*tokens[i]->value()) << std::endl;
   }
#endif

   std::ofstream os;
   os.open(argv[2], std::ios::out | std::ios::binary | std::ios::ate);
   Emit * emit = new Emit(&tokens, &os);
   emit->assemble();
   os.close();

   delete l;
   delete emit;
}