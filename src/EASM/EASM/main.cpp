#include "Lexer.h"
#include "TokenType.h"

#include <string>

int main() {
   const char * code = "li R1, 69 addi R1, 2 mov R3, R1";

   std::vector<Token*> tokens;
   Lexer * l = new Lexer(code, &tokens);
   l->scan();


}