#include "Lexer.h"

Lexer::Lexer(const char * code, std::vector<Token*> * tokes) {
   tokens = tokes;
   pos = 0;
   len = strlen(code);
   source = code;
}


Lexer::~Lexer() {
    for (int i = 0; i < tokens->size(); i++) {
       delete (*tokens)[i];
    }
}

void Lexer::scan() {
   whitespace();

   while (peek_char() != -1) {
      if (isalpha(peek_char())) {
         scan_id();
      }
      else if (isdigit(peek_char())) {
         scan_num();
      }
      else {
         switch (peek_char()) {
         case ',':
            tokens->push_back(new Token(new std::string(","), Comma));
            read_char();
            break;
         case '.':
            scan_label_declaration();
            break;
         default:
            printf("Unknown char %d!", (char)read_char());
            break;
         }
      }
      whitespace();
   }
}
