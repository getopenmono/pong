// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_shared_state_h
#define pong_shared_state_h
#include <stdint.h>

struct SharedState
{
  enum Game
  {
    Init, // 0
    Intermission, // 1
    ComputerServe, // 2
    HumanServe, // 3
    GameOn, // 4
    ComputerMissed, // 5
    HumanMissed, // 6
    GameEnd // 7
  }
  game;
  Game nextGameState;
  uint32_t msNow;
  uint16_t ballX;
  uint16_t computerX;
  uint16_t humanX;
  int encoderPulses;
  char const * crash;

  SharedState ();
  void reset();
  bool operator == (SharedState const & rhs) const;
  bool operator != (SharedState const & rhs) const;
};

#endif // pong_shared_state_h
