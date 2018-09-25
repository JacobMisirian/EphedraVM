#ifndef _REGISTER_INFO_H_
#define _REGISTER_INFO_H_

#include <vector>
#include <stdint.h>

static const std::vector<std::string> register_identifiers = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "flags", "bp", "ip", "sp" };

static uint8_t get_register_code(std::string * r) {
   auto it = find(register_identifiers.begin(), register_identifiers.end(), *r);
   if (it != register_identifiers.end()) {
      auto ret = (uint8_t)std::distance(register_identifiers.begin(), it);
      return ret;
   }
}

#endif