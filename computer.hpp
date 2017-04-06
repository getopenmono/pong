// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_computer_h
#define pong_computer_h
#include <mono.h>
#include "itickable.hpp"

class Computer
:
  public ITickable,
  public mono::ui::View
{
public:
  Computer (mono::geo::Rect const & rectangle);
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_computer_h
