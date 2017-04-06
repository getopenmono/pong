// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_shared_state_h
#define pong_shared_state_h

struct SharedState
{
  enum Game
  {
    Reset,
    WaitingForPlayersToReturnToCenter,
    Sleep
  }
  game;
  int msNow;
  int msBedTime;
  int encoderPulses;

  SharedState ();
};

#endif // pong_shared_state_h
