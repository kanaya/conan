#include <MIDI.h>
#include <Servo.h>

MIDI_CREATE_DEFAULT_INSTANCE();

Servo servo0;
Servo servo1;
Servo servo2;
Servo servos[] = { servo0, servo1, servo2 };
const int servo_pins[] = { 6, 9, 10 };
const int STOP = 90;

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks

void handleNoteOn(byte channel, byte pitch, byte velocity) {
    // Do whatever you want when a note is pressed.

    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
    char buff[255];
    sprintf(buff, "channel = %d, pitch = %d, velocity = %d", channel, pitch, velocity);
    Serial.println(buff);
    int s = pitch - 60;
    if (s >= 0 && s < 3) {
      if (velocity > 0) {
        int v = map(velocity, 1, 127, 0, 180);
        servos[s].write(v);
      }
    }
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    char buff[255];
    sprintf(buff, "channel = %d, pitch = %d, velocity = %d", channel, pitch, velocity);
    Serial.println(buff);
    int s = pitch - 60;
    if (s >= 0 && s < 3) {
      servos[s].write(STOP);
    }
}

// -----------------------------------------------------------------------------

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 3; ++i) {
    pinMode(servo_pins[i], OUTPUT);
    servos[i].attach(servo_pins[i], 500, 2400);
    servos[i].write(STOP);
  }

  Serial.begin(9600);
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();

    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
