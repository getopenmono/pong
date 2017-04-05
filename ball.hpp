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
  mono::geo::Point center;
public:
  Ball (mono::geo::Point const & center);
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_ball_h
