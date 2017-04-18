// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "encoder.hpp"
#include "constants.hpp"

Encoder::Encoder (PinName pinA, PinName pinB)
:
  lastA(0),
  lastB(0),
  channelA(pinA),
  channelB(pinB)
{
#ifndef EMUNO
  // Pull up A.
  CyPins_SetPinDriveMode(pinA, CY_PINS_DM_RES_UP);
  CyPins_SetPin(pinA);
  // Pull up B.
  CyPins_SetPinDriveMode(pinB, CY_PINS_DM_RES_UP);
  CyPins_SetPin(pinB);
#endif
  reset();
#ifndef EMUNO
  // Samples every 100µs.
  ticker.attach_us(this, &Encoder::sample, 100);
#endif
}

void Encoder::reset ()
{
  pulses = 0;
}

int Encoder::getPulses ()
{
  return pulses;
}

void Encoder::sample ()
{
  uint8_t a = channelA.read();
  uint8_t b = channelB.read();;
  if (a != lastA || b != lastB)
  {
    translate(a, b);
    lastA = a;
    lastB = b;
  }
}

void Encoder::translate (uint8_t a, uint8_t b)
{
  // 00 -> 01 -> 11 -> 10 -> ... = clockwise rotation.
  if (
    (lastA == 0 && lastB == 0 && a == 0 && b >= 1) ||
    (lastA == 0 && lastB >= 1 && a >= 1 && b >= 1) ||
    (lastA >= 1 && lastB >= 1 && a >= 1 && b == 0) ||
    (lastA >= 1 && lastB == 0 && a == 0 && b == 0)
  )
  {
    ++pulses;
  }
  // 01 -> 00 -> 10 -> 11 -> ... = counter clockwise rotation.
  else if (
    (lastA == 0 && lastB >= 1 && a == 0 && b == 0) ||
    (lastA == 0 && lastB == 0 && a >= 1 && b == 0) ||
    (lastA >= 1 && lastB == 0 && a >= 1 && b >= 1) ||
    (lastA >= 1 && lastB >= 1 && a == 0 && b >= 1)
  )
  {
    --pulses;
  }
}
