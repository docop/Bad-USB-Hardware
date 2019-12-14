
#include "KeyboardBad.h"
#include "Bluetooth.h"
#include "CommandUtils.h"
#include "CommandMappingPress.h"

unsigned long BAUD_RATE = 115200;

unsigned int numRepeat = 0,
             indexRepeat = 0,
             indexMain = 0;

KeyboardBad *keyboard = new KeyboardBad();
Bluetooth *bluetooth = new Bluetooth(&BAUD_RATE);

void setup() {
  Serial.begin(BAUD_RATE);
  
  keyboard->begin();
  bluetooth->begin(bluetoothDataReceived);
}

void loop() {
  bluetooth->refresh();

  if (Serial.available() > 0) {
    String payload = Serial.readStringUntil(0x03);
    Serial.println(payload);
    commandPromptParser(payload);
  }
}

void bluetoothDataReceived(String payload)
{
  Serial.println(payload);
  commandPromptParser(payload);
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
      keyboard->setDelay(parameter.toInt());
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
    keyboard->write(parameter);
    return true;
  }
  return false;
}

bool commandMappingPress(String command) {
  if (command.length() == 1) {
    keyboard->press(command[0]);
    return true;
  }

  for (byte i = 0; i < COUNT_KEYS_PRESS; i++) {
    CommandPress commandPress = CommandMappingPress[i];
    if (command.equals(commandPress.Key)) {
      keyboard->press(commandPress.Value);
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
    keyboard->releaseAll();
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
