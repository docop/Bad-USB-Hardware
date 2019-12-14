#include "KeyboardFacade.h"
#include "Keyboard.h"

void KeyboardFacade::write(String command)
{
  write(command, 10);
}

void KeyboardFacade::write(String command, unsigned int delayDefault)
{
  for (byte i = 0, l = command.length(); i < l; i++) {
    Keyboard.write(command.charAt(i));
  }
  releaseAll(delayDefault);
}

void KeyboardFacade::press(byte command)
{
  Keyboard.press(command);
}

void KeyboardFacade::releaseAll(unsigned int delayDefault)
{
  Keyboard.releaseAll();
  delay(delayDefault);
}
