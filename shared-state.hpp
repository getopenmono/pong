// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_shared_state_h
#define pong_shared_state_h
#include <stdint.h>

struct SharedState
{
  enum Game
  {
    Reset,
    WaitingForHumanToReturnToCenter,
    ComputerToServe,
    GameOn,
    Sleep
  }
  game;
  int msNow;
  int msBedTime;
  int encoderPulses;
  bool humanReady;
  uint16_t ballX;
  uint16_t ballY;
  bool computerHasBall;
  bool computerMissedBall;
  bool humanHasBall;
  bool humanMissedBall;

  SharedState ();
  bool operator == (SharedState const & rhs);
  bool operator != (SharedState const & rhs);
  void reset ();
};

#endif // pong_shared_state_h
