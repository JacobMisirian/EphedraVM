#include "Emit.h"
#include <fstream>
#include "Lexer.h"
#include <string>
#include "TokenType.h"

int main(int argc, char *argv[]) {
   const char * code = "li R1, 69 addi R1, 2 mov R3, R1";

   std::vector<Token*> tokens;
   Lexer * l = new Lexer(code, &tokens);
   l->scan();

   std::ofstream os;
   os.open(argv[1], std::ios::out | std::ios::binary | std::ios::ate);
   Emit * emit = new Emit(&tokens, &os);
   os.close();
}