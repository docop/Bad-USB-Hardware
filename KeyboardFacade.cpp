#include "KeyboardFacade.h"
#include "Keyboard.h"

void KeyboardFacade::write(String command)
{
  write(command, 10);
}

void KeyboardFacade::write(String command, unsigned int delayDefault)
{
  for (unsigned int i = 0; i < command.length(); i++) {
    Keyboard.write(command.charAt(i));
  }
  releaseAll(delayDefault);
}

void KeyboardFacade::press(unsigned int command)
{
  Keyboard.press(command);
}

void KeyboardFacade::releaseAll(unsigned int delayDefault)
{
  Keyboard.releaseAll();
  delay(delayDefault);
}
