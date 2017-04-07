// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_shared_state_h
#define pong_shared_state_h
#include <stdint.h>

struct SharedState
{
  enum Game
  {
    Reset, // 0
    WaitingForHumanToReturnToCenter, // 1
    ComputerToServe, // 2
    GameOn, // 3
    Sleep,
    Crashed
  }
  game;
  char const * crash;
  int msNow;
  int msBedTime;
  int encoderPulses;
  bool humanReady;
  uint16_t ballX;
  uint16_t ballY;
  uint16_t computerX;
  uint16_t humanX;
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
