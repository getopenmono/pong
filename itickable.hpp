// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_itickable_h
#define pong_itickable_h
#include "shared-state.hpp"

/**
 * All visible objects in the game implement this interface, which only
 * requires that the object can be ticked by a global scheduler.  The only way
 * that objects can communicate with each other is though the shared state
 * provided through the tick.
 */

class ITickable
{
public:
  virtual char const * getName () const = 0;
  virtual void tick (SharedState & state) = 0;
};

#endif // pong_itickable_h
