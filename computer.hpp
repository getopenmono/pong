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
  Rng rng;
  void erase ();
  void followBall (uint16_t ballX);
  bool calculateHasBall (uint16_t ballX, uint16_t ballY);
public:
  Computer ();
  virtual void repaint ();
  virtual char const * getName () const { return "Computer"; };
  virtual void tick (SharedState & state);
};

#endif // pong_computer_h
