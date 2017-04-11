// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "shared-state.hpp"
#include "constants.hpp"

SharedState::SharedState ()
{
  reset();
}

void SharedState::reset ()
{
  game = Intermission;
  msNow = 0;
  computerX = 0;
  humanX = 0;
  computerMissed = false;
  humanMissed = false;
  encoderPulses = 0;
  crash = 0;
}
