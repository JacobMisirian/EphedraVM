#ifndef _TEXT_SCREEN_H_
#define _TEXT_SCREEN_H_

#include "Device.h"
#include "CPU.h"
#include <chrono>
#include <thread>
#ifdef _OS_WINDOWS_
#include <Windows.h>
#endif

class TextScreen : public Device {
public:
   TextScreen(char * ram) { mem_ptr = ram; th = NULL; }
   ~TextScreen() { if (th != NULL) delete th; }
   void power_on();
   void power_off();
private:
   static const int DEFAULT_TICK_FREQ = 50;
   static const int TEXT_ADDR = 100;
   static const int TEXT_WIDTH = 80;
   static const int TEXT_HEIGHT = 25;
   char * mem_ptr;
   char text_buff[TEXT_WIDTH * TEXT_HEIGHT];
   int tick_freq;
   std::thread * th;
   void run();
};

#endif