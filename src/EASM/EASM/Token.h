#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include "TokenType.h"

class Token
{
private:
   TokenType token_type;
   std::string * val;
public:
   Token(std::string * val, const TokenType token_type);
   ~Token();
   TokenType tokenType();
   std::string * value();
};

#endif