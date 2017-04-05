// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_scheduler_h
#define pong_scheduler_h
#include <vector>
#include "shared-state.hpp"
#include "itickable.hpp"

/**
 * Container for a set of tickable objects.  When the scheduler is run, it
 * will tick all the contianed objects.
 */

class Scheduler
{
  std::vector<ITickable*> tickables;
public:
  Scheduler ();
  void add (ITickable * tickable);
  void run (SharedState & state);
};

#endif // pong_scheduler_h
