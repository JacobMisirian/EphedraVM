#include "TextScreen.h" 
#include <iostream>
#include <mutex>

std::ostream&
print_one(std::ostream& os)
{
   return os;
}

template <class A0, class ...Args>
std::ostream&
print_one(std::ostream& os, const A0& a0, const Args& ...args)
{
   os << a0;
   return print_one(os, args...);
}

template <class ...Args>
std::ostream&
print(std::ostream& os, const Args& ...args)
{
   return print_one(os, args...);
}

std::mutex&
get_cout_mutex()
{
   static std::mutex m;
   return m;
}

template <class ...Args>
std::ostream&
print(const Args& ...args)
{
   std::lock_guard<std::mutex> _(get_cout_mutex());
   return print(std::cout, args...);
}

void TextScreen::power_on() {
   if (th != NULL) {
      delete th;
   }
   th = new std::thread(&TextScreen::run, this);
}

void TextScreen::power_off() {
   if (th != NULL) {
      th->detach();
      delete th;
      th = NULL;
   }
}

void TextScreen::run() {

   while (true) {
      for (int row = 0; row < TEXT_HEIGHT; row++) {
         for (int col = 0; col < TEXT_WIDTH; col++) {
            uint8_t real_c = mem_ptr[TEXT_ADDR + (row * TEXT_WIDTH) + col];
            uint8_t buff_c = text_buff[(row * TEXT_WIDTH) + col];

            if (buff_c != real_c) {
               text_buff[(row * TEXT_WIDTH) + col] =real_c;
#ifdef _OS_WINDOWS_
               COORD coord;
               coord.X = col;
               coord.Y = row;
               SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
               printf("%c", real_c);
#endif
#ifdef _OS_LINUX_
               printf("\033[%d;%dH%c", row, col, real_c);
               fflush(stdout);
#endif
            }
         }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
   }
}