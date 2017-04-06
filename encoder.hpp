// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_encoder_h
#define pong_encoder_h
#include <mono.h>
#include "itickable.hpp"

class Encoder
:
  public ITickable
{
  int lastPulse;
  void reset (int&);
public:
  Encoder ();
  virtual void tick (SharedState & state);
  virtual void repaint () {}
};

#endif // pong_encoder_h
