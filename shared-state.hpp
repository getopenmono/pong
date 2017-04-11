// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_shared_state_h
#define pong_shared_state_h
#include <stdint.h>

struct SharedState
{
  enum Game
  {
    Intermission, // 0
    ComputerServe, // 1
    HumanServe, // 2
    GameOn, // 3
    UpdateScore, // 4
    GameEnd // 5
  }
  game;
  uint32_t msNow;
  uint16_t ballX;
  uint16_t computerX;
  uint16_t humanX;
  bool computerMissed;
  bool humanMissed;
  int encoderPulses;
  char const * crash;

  SharedState ();
  void reset();
};

#endif // pong_shared_state_h
