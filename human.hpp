// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_human_h
#define pong_human_h
#include <mono.h>
#include "itickable.hpp"

class Human
:
  public ITickable,
  public mono::ui::View
{
public:
  Human (mono::geo::Rect const & rectangle);
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_human_h
