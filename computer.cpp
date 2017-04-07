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
  erase();
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
  if (rng.random31b() % 3 == 0)
    return;
  int x = Position().X();
  int direction = ballX - (x + paddleLength/2);
  if (direction < 0)
    x -= computerSpeed;
  else if (direction > 0)
    x += computerSpeed;
  if (x < 0)
    x = 0;
  else if (x > screenHeight - paddleLength)
    x = screenHeight - paddleLength;
  if (x != Position().X())
  {
    erase();
    setPosition(Point(x, margin));
    repaint();
  }
}

bool Computer::calculateHasBall (uint16_t ballX, uint16_t ballY)
{
  int y = Position().Y();
  if (y + paddleWidth >= ballY)
  {
    int x = Position().X();
    if (x <= ballX && (ballX + 2 * radius) <= (x + paddleLength))
      return true;
  }
  return false;
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
      break;
    case SharedState::GameOn:
      break;
    case SharedState::Sleep:
      return;
    case SharedState::Crashed:
      return;
  }
  followBall(state.ballX);
  state.computerHasBall = calculateHasBall(state.ballX, state.ballY);
  state.computerX = Position().X();

  if (Position().X() < 0)
    state.crash = "computer x negative";
  if (Position().X() + paddleLength > screenHeight)
    state.crash = "computer x too high";
}
