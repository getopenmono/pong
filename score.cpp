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
  eraseDigit(9);
}

void Score::repaint ()
{
  printf("HUMAN %d -- COMPUTER %d\r\n", human, computer);
  drawDigit(computer, 0);
  drawDigit(human, 9);
}

void Score::drawDigit (uint8_t digit, uint16_t yDisplacement)
{
  painter.setForegroundColor(green);
  if (digit == 0)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, 3 * digitWidth, digitWidth);
  }
  else if (digit == 1)
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + (yDisplacement+1) * digitWidth, 5 * digitWidth, digitWidth);
  else if (digit == 2)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + yDisplacement * digitWidth, digitWidth, 2 * digitWidth);
    painter.drawFillRect(ViewRect().X() + digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, 2 * digitWidth);
  }
  else if (digit == 3)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + yDisplacement * digitWidth, digitWidth, 2 * digitWidth);
    painter.drawFillRect(ViewRect().X() + digitWidth, ViewRect().Y() + yDisplacement * digitWidth, digitWidth, 2 * digitWidth);
  }
  else if (digit == 4)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, 2 * digitWidth, digitWidth);
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 2 * digitWidth, 2 * digitWidth);
  }
  else if (digit == 5)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, 2 * digitWidth);
    painter.drawFillRect(ViewRect().X() + digitWidth, ViewRect().Y() + yDisplacement * digitWidth, digitWidth, 2 * digitWidth);
  }
  else if (digit == 6)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, 2 * digitWidth);
    painter.drawFillRect(ViewRect().X() + digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, digitWidth);
  }
  else if (digit == 7)
  {
    painter.drawFillRect(ViewRect().X() + 4*digitWidth, ViewRect().Y() + yDisplacement * digitWidth, digitWidth, 3 * digitWidth);
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + (yDisplacement+2) * digitWidth, 4 * digitWidth, digitWidth);
  }
  else if (digit == 8)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, digitWidth);
    painter.drawFillRect(ViewRect().X() + digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, digitWidth);
  }
  else if (digit == 9)
  {
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
    painter.setForegroundColor(black);
    painter.drawFillRect(ViewRect().X() + 3*digitWidth, ViewRect().Y() + (yDisplacement+1) * digitWidth, digitWidth, digitWidth);
    painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 2 * digitWidth, 2 * digitWidth);
  }
}

void Score::eraseDigit (uint16_t yDisplacement)
{
  painter.setForegroundColor(black);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y() + yDisplacement * digitWidth, 5 * digitWidth, 3 * digitWidth);
}

