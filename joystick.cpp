// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "joystick.hpp"
#include "constants.hpp"

Joystick::Joystick ()
:
  encoder(J_RING1, J_RING2)
{
}

void Joystick::tick (SharedState & state)
{
  int pulses = encoder.getPulses();
  if (pulses != state.encoderPulses)
  {
    state.encoderPulses = pulses;
  }
}
