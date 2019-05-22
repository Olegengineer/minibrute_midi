#ifndef Controller_h
#define Controller_h
#include <Arduino.h>

class Button
{
public:
  Button(byte pin, byte command, byte value, byte channel, byte debounce);
  byte getValue();
  void newValue(byte command, byte value, byte channel);
  byte Bcommand;
  byte Bvalue;
  byte Bchannel;
  byte Btoggle;

private:
  byte _previous;
  byte _current;
  unsigned long _time;
  int _debounce;
  byte _pin;
  byte _value;
  byte _command;
  bool _busy;
  byte _status;
  byte _last;
  byte _enablepin;
};
#endif
