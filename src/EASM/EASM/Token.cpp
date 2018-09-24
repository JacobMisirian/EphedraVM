#include "Token.h"

Token::Token(std::string * val, const TokenType token_type) {
   Token::val = val;

   Token::token_type = token_type;
}

Token::~Token() {
   delete val;
}

TokenType Token::tokenType() {
   return token_type;
}

std::string * Token::value(){
   return val;
}