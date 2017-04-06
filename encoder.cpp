// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "encoder.hpp"
#include "constants.hpp"

Encoder::Encoder ()
:
  lastPulse(0)
{
}

void Encoder::reset (int & sharedPulses)
{
  lastPulse = 0;
  sharedPulses = 0;
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
    case SharedState::Sleep:
      return;
  }
  randomMove(state.encoderPulses);
}

void Encoder::randomMove (int & sharedPulses)
{
  static int direction = 1;
  sharedPulses += direction;
  if (sharedPulses > screenHeight/2/pulsesPerPixel || sharedPulses < -screenHeight/2/pulsesPerPixel)
    direction = -direction;
}
