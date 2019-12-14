#include "CommandUtils.h"

CommandPrompt CommandUtils::split(String source)
{
  String command = "";
  String parameter = "";
  for (byte i = 0, l = source.length() - 1; i <= l; i++)
  {
    const char character = source.charAt(i);

    if (isSpace(character))
    {
      command.toLowerCase();
      command.trim();

      parameter = source.substring(i);
      parameter.trim();

      return {command, parameter};
    }

    command += character;

    if (i == l)
    {
      command.trim();
      command.toLowerCase();

      return {command, ""};
    }
  }
}

bool CommandUtils::isNumber(String source) {
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
