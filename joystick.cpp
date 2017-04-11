// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "joystick.hpp"
#include "constants.hpp"

Joystick::Joystick ()
:
  encoder(J_RING1, J_RING2)
{
}

void Joystick::reset (int & sharedPulses)
{
  sharedPulses = encoder.getPulses();
}

void Joystick::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Reset:
      return reset(state.encoderPulses);
    case SharedState::WaitingForHumanToReturnToCenter:
      break;
    case SharedState::ComputerToServe:
      break;
    case SharedState::GameOn:
      break;
    case SharedState::Sleep:
      return;
    case SharedState::Crashed:
      return;
  }
  int pulses = encoder.getPulses();
  state.encoderPulses = pulses;
}
