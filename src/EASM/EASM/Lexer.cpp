#include "Lexer.h"

Lexer::Lexer(std::ifstream * src, std::vector<Token*> * tokes) {
   tokens = tokes;
   pos = 0;
   source = src;
}


Lexer::~Lexer() {
    for (int i = 0; i < tokens->size(); i++) {
       delete (*tokens)[i];
    }
    delete source;
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
