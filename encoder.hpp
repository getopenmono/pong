// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_encoder_h
#define pong_encoder_h
#include <mono.h>
#include <mbed.h>

class Encoder
{
  int pulses;
  uint8 lastA;
  uint8 lastB;
  mbed::DigitalIn channelA;
  mbed::DigitalIn channelB;
  mbed::Ticker ticker;
  void translate (uint8_t a, uint8_t b);
  void sample ();
public:
  Encoder (PinName pinA, PinName pinB);
  void reset ();
  int getPulses ();
};

#endif // pong_encoder_h
