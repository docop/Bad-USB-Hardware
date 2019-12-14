#pragma once
#include "Arduino.h"

class KeyboardFacade
{
  public:
    static void write(String command);

    static void write(String command, unsigned int delayDefault);

    static void press(byte command);

    static void releaseAll(unsigned int delay);
};
