#ifndef _CPU_H_
#define _CPU_H_

#include "Device.h"
#include <fstream>
#include "Instruction.h"
#include "Register.h"
#include <stdint.h>
#include <stdio.h>
#include "TextScreen.h"
#include <vector>

#define _OS_WINDOWS_
// #define _OS_LINUX_

class CPU {
public:
   CPU(size_t ram_size, FILE * os);
   ~CPU();
   void execute();
   char * get_ram_ptr() { return ram; }
   void add_device(Device * d) { devices->push_back(d); }
private:
   char * ram;
   int16_t registers[16];
   std::vector<Device*> * devices;
   void start_devices();
   void stop_devices();
};

#endif