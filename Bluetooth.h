#pragma once
#include "Arduino.h"

typedef void (*BluetoothDataReceived)(String payload);

class Bluetooth
{
  protected:
    unsigned long *baudRate;
    char terminator = 0x03;
    BluetoothDataReceived dataReceived;

  public:
    Bluetooth(unsigned long *baudRate);
    void begin(BluetoothDataReceived callback);
    void refresh(void);
};
