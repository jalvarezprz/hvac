#include "led.h"

led::led(uint8_t pin)
{
   this->pin = pin;
}

led::~led() {}

void led::init(bool state)
{
   pinMode(pin, OUTPUT);
   if (state == HIGH)
      on();
   else
      off();
}

void led::on()
{
   digitalWrite(pin, HIGH);
}

void led::off()
{
   digitalWrite(pin, LOW);
}