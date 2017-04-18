// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_human_h
#define pong_human_h
#include <mono.h>
#include "itickable.hpp"
#include "rng.hpp"

class Human
:
  public ITickable,
  public mono::ui::View
{
  int x;
  Rng rng;
  void erase ();
  void followEncoder (int encoderPulses);
  void followBall (uint16_t ballX);
  int lastPulses;
public:
  Human ();
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_human_h
