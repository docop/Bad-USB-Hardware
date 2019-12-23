#include "KeyboardBad.h"

void KeyboardBad::begin(void) {
  Keyboard.begin();
  this->delayDefault = DELAY_DEFAULT;
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
  delay(this->delayDefault);
}

void KeyboardBad::setDelay(unsigned int value) {
  this->delayDefault = value;
}
