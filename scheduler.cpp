// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "scheduler.hpp"

Scheduler::Scheduler ()
{
}

void Scheduler::add (ITickable * tickable)
{
  tickables.push_back(tickable);
}

void Scheduler::run (SharedState & state)
{
  for (std::vector<ITickable*>::iterator i = tickables.begin(); i != tickables.end(); ++i)
  {
    (*i)->tick(state);
    (*i)->repaint();
  }
}
