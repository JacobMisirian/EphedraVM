#include "Emit.h"

Emit::Emit(std::vector<Token*> * tokens, std::ofstream * os) {
   Emit::tokens = tokens;
   Emit::os = os;
}

Emit::~Emit() {
}

void Emit::assemble() {

}