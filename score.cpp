// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include <mono.h>
#include "score.hpp"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

Score::Score ()
:
  View(Rect(
    screenHeight - 6 * digitWidth,
    screenWidth / 2 - 6 * digitWidth,
    5 * digitWidth,
    12 * digitWidth
  ))
{
  reset();
}

void Score::reset ()
{
  computer = 0;
  human = 0;
}

void Score::erase ()
{
}

void Score::repaint ()
{
  /*
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), 5 * digitWidth, 3 * digitWidth);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y() + 9 * digitWidth, 5 * digitWidth, 3 * digitWidth);
  */
}

void Score::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Reset:
      reset();
      repaint();
      break;
    case SharedState::WaitingForHumanToReturnToCenter:
      return;
    case SharedState::ComputerToServe:
      break;
    case SharedState::GameOn:
      break;
    case SharedState::Sleep:
      return;
    case SharedState::Crashed:
      return;
  }
}
