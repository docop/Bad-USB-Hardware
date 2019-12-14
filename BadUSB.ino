
#include "Keyboard.h"
#include "KeyboardFacade.h"
#include "CommandUtils.h"
#include "CommandMappingPress.h"

#define bluetooth Serial1
const unsigned int BAUDRATE = 9600;

unsigned int numRepeat = 0,
             indexRepeat = 0,
             indexMain = 0,
             delayDefault = 10;

void setup() {
  Keyboard.begin();
  Serial.begin(BAUDRATE);
  bluetooth.begin(BAUDRATE);
}

void loop() {
  if (bluetooth.available() > 0) {
    String payload = bluetooth.readStringUntil(0x03);
    Serial.println(payload);
    commandPromptParser(payload);
  }

  if (Serial.available() > 0) {
    String payload = Serial.readStringUntil(0x03);
    Serial.println(payload);
    commandPromptParser(payload);
  }
}

bool commandNoResult(String command, String parameter) {
  if (command.equals("rem")) {
    return true;
  }

  if (command.equals("delay")) {
    if (CommandUtils::isNumber(parameter)) {
      delay(parameter.toInt());
    }
    return true;
  }

  if (command.equals("delaydefault")) {
    if (CommandUtils::isNumber(parameter)) {
      delayDefault = parameter.toInt();
    }
    return true;
  }

  if (command.equals("repeat")) {
    if (CommandUtils::isNumber(parameter)) {
      numRepeat = parameter.toInt() - 1;
      indexRepeat = indexMain;
    }
    return true;
  }

  if (command.equals("repeatend")) {
    if (numRepeat > 0) {
      indexMain = indexRepeat;
      --numRepeat;
    }
    return true;
  }
  return false;
}

bool commandWrite(String command, String parameter) {
  if (command == "string") {
    KeyboardFacade::write(parameter, delayDefault);
    return true;
  }
  return false;
}

bool commandMappingPress(String command) {
  if (command.length() == 1) {
    KeyboardFacade::press(command[0]);
    return true;
  }

  for (byte i = 0; i < COUNT_KEYS_PRESS; i++) {
    CommandPress commandPress = CommandMappingPress[i];
    if (command.equals(commandPress.Key)) {
      KeyboardFacade::press(commandPress.Value);
      return true;
    }
  }

  return false;
}

bool commandPress(String command, String parameter) {
  if (commandMappingPress(command)) {
    if (parameter.length() > 0) {
      CommandPrompt prompt = CommandUtils::split(parameter);
      if (prompt.command.length() > 0) {
        commandPress(prompt.command, prompt.parameter);
        return true;
      }
    }
    KeyboardFacade::releaseAll(delayDefault);
    return true;
  }
  return false;
}

bool commandPromptParser(String source) {
  bool inside = false;
  unsigned int length = 0;
  String commandPrompt = "";

  for (indexMain = 0, length = source.length(); indexMain < length; indexMain++) {
    const char character = source.charAt(indexMain);
    if (character == '<') {
      inside = true;
      continue;
    }

    if (character == '>') {
      commandPrompt.trim();

      if (commandPrompt.length() > 0) {
        CommandPrompt prompt = CommandUtils::split(commandPrompt);

        commandNoResult(prompt.command, prompt.parameter)
        || commandWrite(prompt.command, prompt.parameter)
        || commandPress(prompt.command, prompt.parameter);

        commandPrompt = "";
      }
      inside = false;
      continue;
    }

    if (inside) {
      commandPrompt += character;
    }
  }
}
