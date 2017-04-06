// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "computer.hpp"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

Computer::Computer ()
:
  View(Rect(0, 0, paddleLength, paddleWidth))
{
}

void Computer::reset ()
{
  setPosition(Point(100, margin));
}

void Computer::erase ()
{
  painter.setBackgroundColor(black);
  painter.drawFillRect(ViewRect(), true);
}

void Computer::repaint ()
{
  painter.setBackgroundColor(green);
  painter.drawFillRect(ViewRect(), true);
}

void Computer::followBall (uint16_t ballX)
{
  int x = Position().X();
  int direction = ballX - (x + paddleLength/2);
  if (direction < 0)
    x -= computerSpeed;
  else if (direction > 0)
    x += computerSpeed;
  if (x != Position().X())
  {
    erase();
    setPosition(Point(x, margin));
    repaint();
  }
}

void Computer::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Reset:
      reset();
      repaint();
      return;
    case SharedState::WaitingForHumanToReturnToCenter:
      return;
    case SharedState::ComputerToServe:
      // TODO: serve
      break;
    case SharedState::Sleep:
      return;
  }
  followBall(state.ballX);
}
