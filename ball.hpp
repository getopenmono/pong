// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_ball_h
#define pong_ball_h
#include <mono.h>

class Ball
:
  public mono::ui::View
{
  mono::geo::Point center;
public:
  Ball (mono::geo::Point const & center);
  virtual void repaint ();
};

#endif // pong_ball_h
