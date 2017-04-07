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
  game = Reset;
  crash = 0;
  msNow = 0;
  encoderPulses = 0;
  humanReady = false;
  //computerHasBall = false;
  computerMissedBall = false;
  humanHasBall = false;
  humanMissedBall = false;
  computerX = 0;
  humanX = 0;
  ballX = screenHeight / 2;
  ballY = screenWidth / 2;
}

bool SharedState::operator == (SharedState const & rhs)
{
  if (game != rhs.game) return false;
  if (crash != rhs.crash) return false;
  if (msBedTime != rhs.msBedTime) return false;
  // if (encoderPulses != rhs.encoderPulses) return false;
  if (humanReady != rhs.humanReady) return false;
  // if (ballX != rhs.ballX) return false;
  if (computerHasBall != rhs.computerHasBall) return false;
  if (computerMissedBall != rhs.computerMissedBall) return false;
  if (humanHasBall != rhs.humanHasBall) return false;
  if (humanMissedBall != rhs.humanMissedBall) return false;
  return true;
}

bool SharedState::operator != (SharedState const & rhs)
{
  return ! ((*this) == rhs);
}
