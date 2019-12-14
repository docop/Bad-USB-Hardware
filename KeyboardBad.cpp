#include "KeyboardBad.h"

void KeyboardBad::begin(void) {
  Keyboard.begin();
}

void KeyboardBad::write(String command)
{
  for (byte i = 0, l = command.length(); i < l; i++) {
    Keyboard.write(command.charAt(i));
  }
  releaseAll();
}

void KeyboardBad::press(byte command)
{
  Keyboard.press(command);
}

void KeyboardBad::releaseAll()
{
  Keyboard.releaseAll();
  delay(DELAY_DEFAULT);
}

void KeyboardBad::setDelay(unsigned int value) {
  DELAY_DEFAULT = value;
}
