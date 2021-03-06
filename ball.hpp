// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_ball_h
#define pong_ball_h
#include <mono.h>
#include "itickable.hpp"

class Ball
:
  public ITickable,
  public mono::ui::View
{
  /* To avoid floating point calculations, these Thou variables represent
     1/1024 of the actual value, ie., they are "scaled integers".
   */
  int thouXDirection;
  int thouYDirection;
  int thouX;
  int thouY;

  mono::sensor::IBuzzer & buzzer;
  void reset ();
  void erase ();
  void moveBallTo (uint16_t & x);
  void stepBall (SharedState & state);
  mono::geo::Point effectuateDirection ();
  mono::geo::Point calculateNextPosition (uint16_t computerX, uint16_t humanX);
public:
  Ball ();
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_ball_h
