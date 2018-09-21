#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <iostream>
#include <stdint.h>

#define IP_REGISTER registers[get_register(IP)]


enum RegisterNames {
   R1,
   R2,
   R3,
   R4,
   Flags = 0xC,
   BP = 0xD,
   IP = 0xE,
   SP = 0xF
};

static int8_t get_register(RegisterNames r) {
   return (int8_t)r;
}

#endif