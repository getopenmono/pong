// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "encoder.hpp"

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
    case SharedState::WaitingForPlayersToReturnToCenter:
      return;
    case SharedState::Sleep:
      return;
  }
}
