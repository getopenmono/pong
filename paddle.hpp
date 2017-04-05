// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_paddle_h
#define pong_paddle_h
#include <mono.h>
#include "itickable.hpp"

class Paddle
:
  public ITickable,
  public mono::ui::View
{
public:
  Paddle (mono::geo::Rect const & rectangle);
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_paddle_h
