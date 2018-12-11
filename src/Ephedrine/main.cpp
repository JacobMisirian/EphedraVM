#include "Device.h"
#include "TextScreen.h"
#include "CPU.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
   FILE * os = fopen(argv[1], "rb");
   CPU * cpu = new CPU(0xFFFF, os);
   Device * screen = new TextScreen(cpu->get_ram_ptr());
   cpu->add_device(screen);
   cpu->execute();
   fclose(os);
   delete cpu;
}