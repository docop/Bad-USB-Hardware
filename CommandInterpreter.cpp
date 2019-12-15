#include "CommandInterpreter.h"
#include "CommandMappingPress.h"

CommandInterpreter::CommandInterpreter(KeyboardBad *keyboard) {
  this->keyboard = keyboard;
}

void CommandInterpreter::setSource(String source)
{
  this->source = source;
}

void CommandInterpreter::processing(void)
{
  String commandPrompt = "";

  this->repeat = {0, 0};
  this->iterator = {0, source.length(), false };
  
  for (; this->iterator.index < this->iterator.length; this->iterator.index++)
  {
    const char _char = source.charAt(this->iterator.index);
    if (_char == '<') {
      this->iterator.inside = true;
      continue;
    }

    if (_char == '>') {
      commandPrompt.trim();

      if (commandPrompt.length() > 0) {
        CommandPrompt prompt = this->split(commandPrompt);

        this->notPressKeyboard(prompt.command, prompt.parameter)
        || this->writeKeyboard(prompt.command, prompt.parameter)
        || this->pressKeyboard(prompt.command, prompt.parameter);

        commandPrompt = "";
      }
      this->iterator.inside = false;
      continue;
    }

    if (this->iterator.inside) {
      commandPrompt += _char;
    }
  }
}

bool CommandInterpreter::notPressKeyboard(String command, String parameter) {
  if (command.equals("rem")) {
    return true;
  }

  if (command.equals("delay")) {
    if (this->isNumber(parameter)) {
      delay(parameter.toInt());
    }
    return true;
  }

  if (command.equals("delaydefault")) {
    if (this->isNumber(parameter)) {
      this->keyboard->setDelay(parameter.toInt());
    }
    return true;
  }

  if (command.equals("repeat")) {
    if (this->isNumber(parameter)) {
      this->repeat.number = parameter.toInt() - 1;
      this->repeat.index = this->iterator.index;
    }
    return true;
  }

  if (command.equals("repeatend")) {
    if (this->repeat.number > 0) {
      this->iterator.index = this->repeat.index;
      --this->repeat.number;
    }
    return true;
  }

  return false;
}

bool CommandInterpreter::writeKeyboard(String command, String parameter) {
  if (command == "string") {
    this->keyboard->write(parameter);
    return true;
  }

  return false;
}

bool CommandInterpreter::mappingPress(String command) {
  if (command.length() == 1) {
    this->keyboard->press(command[0]);
    return true;
  }

  for (byte i = 0; i < COUNT_KEYS_PRESS; i++) {
    CommandPress commandPress = CommandMappingPress[i];
    if (command.equals(commandPress.Key)) {
      this->keyboard->press(commandPress.Value);
      return true;
    }
  }

  return false;
}

bool CommandInterpreter::pressKeyboard(String command, String parameter) {
  if (this->mappingPress(command)) {
    if (parameter.length() > 0) {
      CommandPrompt prompt = this->split(parameter);
      if (prompt.command.length() > 0) {
        this->pressKeyboard(prompt.command, prompt.parameter);
        return true;
      }
    }
    this->keyboard->releaseAll();
    return true;
  }

  return false;
}

CommandPrompt CommandInterpreter::split(String source)
{
  String command = "";
  String parameter = "";

  for (byte i = 0, l = source.length() - 1; i <= l; i++)
  {
    const char _char = source.charAt(i);

    if (isSpace(_char))
    {
      command.toLowerCase();
      command.trim();

      parameter = source.substring(i);
      parameter.trim();

      return {command, parameter};
    }

    command += _char;

    if (i == l)
    {
      command.trim();
      command.toLowerCase();

      return {command, ""};
    }
  }
}

bool CommandInterpreter::isNumber(String source) {
  if (source.length() == 0) {
    return false;
  }

  for (byte i = 0, l = source.length(); i < l; i++)
  {
    if (!isDigit(source.charAt(i))) {
      return false;
    }
  }

  return true;
}
