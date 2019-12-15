
#include "KeyboardBad.h"
#include "Bluetooth.h"
#include "CommandInterpreter.h"

unsigned long BAUDRATE = 115200;

KeyboardBad *keyboard = new KeyboardBad();
Bluetooth *bluetooth = new Bluetooth(&BAUDRATE);
CommandInterpreter *interpreter = new CommandInterpreter(keyboard);

void setup() {
  Serial.begin(BAUDRATE);

  keyboard->begin();
  bluetooth->begin(bluetoothDataReceived);
}

void loop() {
  bluetooth->refresh();

  if (Serial.available() > 0) {
    String payload = Serial.readStringUntil(0x03);
    Serial.println(payload);
    interpreter->setSource(payload);
    interpreter->processing();
  }
}

void bluetoothDataReceived(String payload)
{
  Serial.println(payload);
  interpreter->setSource(payload);
  interpreter->processing();
}
