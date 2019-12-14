#pragma once
#include "Arduino.h"

struct CommandPrompt {
  String command;
  String parameter;
};

class CommandUtils
{
  public:
    static CommandPrompt split(String source);

    static bool isNumber (String source);
};
