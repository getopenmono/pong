// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_computer_h
#define pong_computer_h
#include <mono.h>
#include "itickable.hpp"
#include "rng.hpp"

class Computer
:
  public ITickable,
  public mono::ui::View
{
  int x;
  Rng rng;
  void followBall (uint16_t ballX);
public:
  Computer ();
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_computer_h
