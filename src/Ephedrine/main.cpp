#include "CPU.h"

#include <stdio.h>


int main(int argc, char *argv[]) {
   FILE * os = fopen(argv[1], "rb");
   CPU * cpu = new CPU(0xFFFF, os);
   cpu->execute();
   fclose(os);
   delete cpu;
}