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
}

void Score::tick (SharedState & state)
{
  if (state.game == SharedState::Init)
  {
    computer = 0;
    human = 0;
    humanToServe = false;
    setupIntermission(state);
  }
  else if (state.game == SharedState::ComputerMissed)
  {
    ++human;
    humanToServe = true;
    setupIntermission(state);
  }
  else if (state.game == SharedState::HumanMissed)
  {
    ++computer;
    humanToServe = false;
    setupIntermission(state);
  }
  else if (state.game == SharedState::Intermission)
  {
    if (state.msNow >= msEndOfIntermission)
    {
      erase();
      if (humanToServe)
        state.nextGameState = SharedState::HumanServe;
      else
        state.nextGameState = SharedState::ComputerServe;
    }
  }
}

void Score::setupIntermission (SharedState & state)
{
  msEndOfIntermission = state.msNow + msIntermission;
  state.nextGameState = SharedState::Intermission;
  repaint();
}

void Score::erase ()
{
  printf("NEXT BALL\r\n");
}

void Score::repaint ()
{
  printf("HUMAN %d -- COMPUTER %d\r\n", human, computer);
  /*
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), 5 * digitWidth, 3 * digitWidth);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y() + 9 * digitWidth, 5 * digitWidth, 3 * digitWidth);
  */
}
