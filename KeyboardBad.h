#pragma once
#include "Arduino.h"
#include "Keyboard.h"

class KeyboardBad
{
  private:
    unsigned int DELAY_DEFAULT = 10;

  public:
    void begin(void);
    void write(String command);
    void press(byte command);
    void releaseAll();
    
    void setDelay(unsigned int value);
};
