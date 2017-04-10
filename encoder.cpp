// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "encoder.hpp"
#include "constants.hpp"

Encoder::Encoder ()
:
  qei(J_RING1, J_RING2, NC, 24)
{
  CyPins_SetPinDriveMode(J_RING1, CY_PINS_DM_RES_UP);
  CyPins_SetPin(J_RING1);
  CyPins_SetPinDriveMode(J_RING2, CY_PINS_DM_RES_UP);
  CyPins_SetPin(J_RING2);
}

void Encoder::reset (int & sharedPulses)
{
  sharedPulses = qei.getPulses();
}

void Encoder::tick (SharedState & state)
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
  int pulses = qei.getPulses();
  int diff = pulses - state.encoderPulses;
  // if (diff > 10 || diff < -10)
    // printf("diff=%d\r\n", diff);
  state.encoderPulses = pulses;
}
