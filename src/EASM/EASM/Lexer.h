#ifndef _LEXER_H_
#define _LEXER_H_

#include "InstructionInfo.h"
#include <iostream>
#include <map>
#include "RegisterInfo.h"
#include "Token.h"
#include <vector>

class Lexer
{
private:
   std::vector<Token*> * tokens;
   int pos;
   int len;
   const char * source;

   int read_char() {
      return pos < len ? source[pos++] : -1;
   }

   int peek_char() {
      return pos < len ? source[pos] : -1;
   }

   void whitespace() {
      while (peek_char() != -1 && isspace(peek_char()))
         read_char();
   }

   void scan_id() {
      std::string * str = new std::string;

      while (peek_char() != -1 && isalnum(peek_char())) {
         (*str) += (char)read_char();
      }

      if (instruction_identifiers.find(*str) != instruction_identifiers.end()) {
         tokens->push_back(new Token(str, Instruction));
      }
      else if (std::find(register_identifiers.begin(), register_identifiers.end(), *str) != register_identifiers.end()) {
         tokens->push_back(new Token(str, Register));
      }
      else {
         tokens->push_back(new Token(str, LabelRequest));
      }
   }

   void scan_label_declaration() {
      read_char(); // .
      std::string * str = new std::string;

      while (peek_char() != -1 && isalnum(peek_char())) {
         (*str) += (char)read_char();
      }

      tokens->push_back(new Token(str, LabelDeclaration));
   }

   void scan_num() {
      std::string * str = new std::string;

      while (peek_char() != -1 && isdigit(peek_char())) {
         (*str) += (char)read_char();
      }

      tokens->push_back(new Token(str, Integer));
   }

   void scan_string() {
      read_char(); // "

      std::string * str = new std::string;

      while (peek_char() != -1 && peek_char() != '"') {
         (*str) += (char)read_char();
      }

      read_char(); // "

      tokens->push_back(new Token(str, String));
   }
public:
   Lexer(const char * code, std::vector<Token*> * tokens);
   ~Lexer();
   void scan();
};

#endif