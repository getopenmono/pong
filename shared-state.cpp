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
  game = Init;
  nextGameState = game;
  msNow = 0;
  computerX = 0;
  humanX = 0;
  ballX = 0;
  encoderPulses = 0;
  crash = 0;
}

bool SharedState::operator == (SharedState const & rhs) const
{
  if (game != rhs.game) return false;
  if (nextGameState != rhs.nextGameState) return false;
  //if (encoderPulses != rhs.encoderPulses) return false;
  if (crash != rhs.crash) return false;
  return true;
}

bool SharedState::operator != (SharedState const & rhs) const
{
  return ! ((*this) == rhs);
}
