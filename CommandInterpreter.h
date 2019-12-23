#pragma once
#include "Arduino.h"
#include "KeyboardBad.h"

struct CommandPrompt {
  String command;
  String parameter;
};

class CommandInterpreter
{
  public:
    CommandInterpreter(KeyboardBad *keyboard);
    void setSource(String source);
    void processing(void);

  protected:
    String source;

    struct Repeat {
      unsigned int index;
      unsigned int number;
    } repeat;

    struct Iterator {
      unsigned int index;
      unsigned int length;
      bool inside;
    } iterator;

    KeyboardBad *keyboard;

    bool notPressKeyboard(String command, String parameter);
    bool pressKeyboard(String command, String parameter);
    bool writeKeyboard(String command, String parameter);
    bool mappingPress(String command);

    CommandPrompt getCommandPrompt(String source);
    bool isNumber (String source);
};
