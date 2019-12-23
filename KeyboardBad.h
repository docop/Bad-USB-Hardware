#pragma once
#include "Arduino.h"
#include "Keyboard.h"

const unsigned int DELAY_DEFAULT = 10;

class KeyboardBad
{
  private:
    unsigned int delayDefault;

  public:
    void begin(void);
    void write(String command);
    void press(byte command);
    void releaseAll();

    void setDelay(unsigned int value);
};
