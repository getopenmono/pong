// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_score_h
#define pong_score_h
#include <mono.h>
#include "itickable.hpp"

class Score
:
  public ITickable,
  public mono::ui::View
{
  uint8_t computer;
  uint8_t human;
  bool humanToServe;
  uint32_t msEndOfIntermission;
  void erase ();
  void setupIntermission (SharedState & state);
public:
  Score ();
  virtual void repaint ();
  virtual void tick (SharedState & state);
};

#endif // pong_score_h
