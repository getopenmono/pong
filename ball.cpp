// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "ball.hpp"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

Ball::Ball ()
:
  View(Rect(0, 0, 2 * radius, 2 * radius))
{
}

void Ball::reset ()
{
  uint16_t x = screenHeight/2;
  uint16_t y = screenWidth/2;
  setPosition(Point(x - radius, y - radius));
  xDirection = 0;
  yDirection = 0;
}

void Ball::erase ()
{
  painter.setForegroundColor(black);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2 , radius * 2);
}

void Ball::repaint ()
{
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2 , radius * 2);
}

void Ball::moveBallTo (Point position)
{
  erase();
  setPosition(position);
  repaint();
}

void Ball::computerReturnsBall ()
{
  yDirection = ballSpeed;
  xDirection = -2;
}

void Ball::humanReturnsBall ()
{
  yDirection = -ballSpeed;
  xDirection = 2;
}

void Ball::tick (SharedState & state)
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
      yDirection = -ballSpeed;
      break;
    case SharedState::GameOn:
      if (state.computerHasBall)
        computerReturnsBall();
      else if (state.humanHasBall)
        humanReturnsBall();
      break;
    case SharedState::Sleep:
      return;
  }
  uint16_t x = Position().X() + xDirection;
  uint16_t y = Position().Y() + yDirection;
  if (x != Position().X() || y != Position().Y())
  {
    moveBallTo(Point(x, y));
    state.ballX = x;
    state.ballY = y;
  }
  if (y == 0)
    state.computerMissedBall = true;
  else if (y == screenWidth - 2 * radius)
    state.humanMissedBall = true;
}
