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
  int xDirection;
  int yDirection;
  void reset ();
  void erase ();
  void moveBallTo (mono::geo::Point position, uint16_t & x, uint16_t & y);
  mono::geo::Point calculateNextPosition ();
  void computerReturnsBall ();
  void humanReturnsBall ();
public:
  Ball ();
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_ball_h
