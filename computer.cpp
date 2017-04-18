// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "computer.hpp"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

Computer::Computer ()
:
  View(Rect(100, margin, paddleLength, paddleWidth)),
  x(100)
{
}

void Computer::tick (SharedState & state)
{
  if (state.game == SharedState::GameEnd)
    return;
  if (state.game == SharedState::Init)
    return repaint();
  if (state.game == SharedState::Intermission)
    return;
  if (state.msNow % computerSlowdown != 0)
    return;
  followBall(state.ballX);
  state.computerX = x;

  if (Position().X() < 0)
    state.crash = "computer x negative";
  if (Position().X() + paddleLength > screenHeight)
    state.crash = "computer x too high";
}

void Computer::repaint ()
{
  painter.setBackgroundColor(black);
  // Only erase minimal area to avoid flicker.
  uint16_t oldX = Position().X();
  if (oldX < x)
  {
    painter.drawFillRect(Rect(oldX, margin, x - oldX, paddleWidth), true);
  }
  else if (oldX > x)
  {
    painter.drawFillRect(Rect(x + paddleLength, margin, oldX - x, paddleWidth), true);
  }
  setPosition(Point(x, margin));
  painter.setBackgroundColor(green);
  painter.drawFillRect(ViewRect(), true);
}

void Computer::followBall (uint16_t ballX)
{
  if (rng.random31b() % 3 == 0)
    return;
  int direction = (ballX - 4 + rng.random31b() % 8) - (x + paddleLength/2);
  if (direction < 0)
    x -= 1;
  else if (direction > 0)
    x += 1;
  if (x < 0)
    x = 0;
  else if (x > screenHeight - paddleLength)
    x = screenHeight - paddleLength;
  if (x != Position().X())
    scheduleRepaint();
}
