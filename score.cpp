// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include <mono.h>
#include "score.hpp"
#include "constants.hpp"
#define DW digitWidth

using mono::geo::Point;
using mono::geo::Rect;

Score::Score ()
:
  View(Rect(
    screenHeight - 6 * DW,
    screenWidth / 2 - 8 * DW,
    5 * DW,
    2 * 8 * DW
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
  repaint();
  if (human >= 9 || computer >= 9)
    state.nextGameState = SharedState::GameEnd;
  else
    state.nextGameState = SharedState::Intermission;
}

void Score::erase ()
{
  printf("NEXT BALL\r\n");
  eraseDigit(0);
  eraseDigit(13);
}

void Score::repaint ()
{
  printf("HUMAN %d -- COMPUTER %d\r\n", human, computer);
  drawDigit(computer, 0);
  drawDigit(human, 13);
}

#define BOX(x,y,w,h) painter.drawFillRect(ViewRect().X()+(x)*DW, ViewRect().Y()+(y)*DW, (w)*DW, (h)*DW)

void Score::drawDigit (uint8_t digit, uint16_t yDisplacement)
{
  painter.setForegroundColor(green);
  if (digit == 0)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(1, yDisplacement+1, 3, 1);
  }
  else if (digit == 1)
  {
    BOX(0, yDisplacement+1, 5, 1);
  }
  else if (digit == 2)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement, 1, 2);
    BOX(1, yDisplacement+1, 1, 2);
  }
  else if (digit == 3)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement, 1, 2);
    BOX(1, yDisplacement, 1, 2);
  }
  else if (digit == 4)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement+1, 2, 1);
    BOX(0, yDisplacement, 2, 2);
  }
  else if (digit == 5)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement+1, 1, 2);
    BOX(1, yDisplacement, 1, 2);
  }
  else if (digit == 6)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement+1, 1, 2);
    BOX(1, yDisplacement+1, 1, 1);
  }
  else if (digit == 7)
  {
    BOX(4, yDisplacement, 1, 3);
    BOX(0, yDisplacement+2, 4, 1);
  }
  else if (digit == 8)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement+1, 1, 1);
    BOX(1, yDisplacement+1, 1, 1);
  }
  else if (digit == 9)
  {
    BOX(0, yDisplacement, 5, 3);
    painter.setForegroundColor(black);
    BOX(3, yDisplacement+1, 1, 1);
    BOX(0, yDisplacement, 2, 2);
  }
}

void Score::eraseDigit (uint16_t yDisplacement)
{
  painter.setForegroundColor(black);
  BOX(0, yDisplacement, 5, 3);
}
