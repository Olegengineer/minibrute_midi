#include <MIDI.h>
#include "Controller.h"

MIDI_CREATE_DEFAULT_INSTANCE();

byte NUMBER_BUTTONS = 8;

Button BU1(2, 0, 60, 1, 5 );
Button BU2(3, 0, 61, 1, 5 );
Button BU3(4, 0, 62, 1, 5 );
Button BU4(5, 0, 63, 1, 5 );
Button BU5(6, 0, 64, 1, 5 );
Button BU6(7, 0, 65, 1, 5 );
Button BU7(8, 1, 64, 1, 5 );
Button BU8(9, 2, 64, 1, 5 );

Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};

void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
}

void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
}

void updateButtons() {
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();
    
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 2:
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 1;
          }
          else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}
