#include "CPU.h"
#include <fstream>

int main(int argc, char *argv[]) {
   std::ifstream os;
   os.open(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
   CPU * cpu = new CPU(0xFFF, &os);
   cpu->execute();
   os.close();
   delete cpu;
}