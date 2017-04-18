// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_joystick_h
#define pong_joystick_h
#include <mono.h>
#include "itickable.hpp"
#include "encoder.hpp"

class Joystick
:
  public ITickable
{
  Encoder encoder;
public:
  Joystick ();
  virtual void tick (SharedState & state);
};

#endif // pong_joystick_h
