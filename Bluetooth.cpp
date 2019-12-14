#include "Bluetooth.h"

#define bluetooth Serial1

Bluetooth::Bluetooth(unsigned long *baudRate) {
  this->baudRate = baudRate;
}

void Bluetooth::begin(BluetoothDataReceived callback) {
  while (!bluetooth);
  bluetooth.begin(this->baudRate);
  this->dataReceived = callback;
}

void Bluetooth::refresh(void) {
  if (bluetooth.available() > 0) {
    String payload = bluetooth.readStringUntil(this->terminator);
    this->dataReceived(payload);
  }
}
