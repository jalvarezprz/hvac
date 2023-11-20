#ifndef __LED_H__
#define __LED_H__

#include <Arduino.h>

class led
{
private:
   uint8_t pin;

public:
   led(uint8_t pin);
   ~led();

   void init(bool state);
   void on();
   void off();
}

#endif