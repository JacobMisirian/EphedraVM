#ifndef _DEVICE_H_
#define _DEVICE_H_

class Device {
public:
   virtual void power_on() = 0;
   virtual void power_off() = 0;

};

#endif