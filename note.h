#ifndef NOTE_H
#define NOTE_H

#include "Arduino.h"

class Note {
 public:
  Note(){} // This is kludgy - to allow Note array initialization w/ empty values
  Note(int _frequency, int _duration);//{frequency = _frequency; duration = _duration;};
  ~Note(){};
  int getFrequency(){return frequency;};
  void playDelay(int pin);
  void play(int pin);
  int frequency;  // in Hz
  int period;     // in microseconds
  int duration;   // Music value
  unsigned long length;
};

Note::Note(int _frequency, int _duration) {
  frequency = _frequency;
  period = (1.0/frequency) * 1000000; // Period = reciprical of frequency; then convert to milliseconds
  duration = _duration;
  length = (1.0/duration) * 1000000; // Note ends length microseconds after it starts
}

void Note::playDelay(int pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(period);
  digitalWrite(pin, LOW);
  delayMicroseconds(period);
}

void Note::play(int pin) {
  unsigned long start = micros();       // Current time in microseconds
  bool state = HIGH;          // keep track of current pin state (set high)
  unsigned long off = start + 1000000;
  digitalWrite(pin, state);    // Pin goes HIGH
  unsigned long toggle = start + period;  // Should stay high until toggle (start + period)
  while (micros() < off){
    if (micros() > toggle) {      // If micros > toggle, need to toggle
      state = !state;
      digitalWrite(pin, state);
      toggle = toggle + period;
    }
  }
}

#endif


/* start = 1000
 * state = HIGH
 * off = 1,001,000
 * write high
 * toggle = start + period = 1000 + 2500 = 3500
 * if micros > 
 */