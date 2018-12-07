#ifndef _LEXER_H_
#define _LEXER_H_

#include <fstream>
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
   std::ifstream * source;

   int8_t read_char() {
      return source->get();
   }

   int8_t peek_char() {
      return source->peek();
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
   Lexer(std::ifstream * src, std::vector<Token*> * tokes);
   ~Lexer();
   void scan();
};

#endif