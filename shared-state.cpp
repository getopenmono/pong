// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "shared-state.hpp"

SharedState::SharedState ()
:
  game(Reset),
  msNow(0),
  encoderPulses(0)
{
}
