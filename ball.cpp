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

void Ball::moveBallTo (Point position, uint16_t & x, uint16_t & y)
{
  erase();
  setPosition(position);
  repaint();
  x = position.X();
  y = position.Y();
}

void Ball::computerReturnsBall ()
{
  yDirection = ballSpeed;
  xDirection = -ballSpeed;
}

void Ball::humanReturnsBall ()
{
  yDirection = -ballSpeed;
  xDirection = ballSpeed;
}

Point Ball::calculateNextPosition ()
{
  int x = Position().X() + xDirection;
  int y = Position().Y() + yDirection;
  if (x <= 0)
  {
    xDirection = ballSpeed;
    if (x < 0)
      x = -x;
  }
  else if (x + 2 * radius >= screenHeight)
  {
    xDirection = -ballSpeed;
    if (x  + 2 * radius > screenHeight)
      x = screenHeight-x;
  }
  return Point(x, y);
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
      xDirection = 0;
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
    case SharedState::Crashed:
      return;
  }
  Point corner = calculateNextPosition();
  if (corner.X() != Position().X() || corner.Y() != Position().Y())
    moveBallTo(corner, state.ballX, state.ballY);
  if (corner.Y() == 0)
    state.computerMissedBall = true;
  else if (corner.Y() == screenWidth - 2 * radius)
    state.humanMissedBall = true;

  if (Position().X() < 0)
    state.crash = "ball x negative";
  if (Position().X() + 2 * radius > screenHeight)
    state.crash = "ball x too high";
  if (Position().Y() < 0)
    state.crash = "ball y negative";
  if (Position().Y() + 2 * radius > screenWidth)
    state.crash = "ball y too high";

  // TEST
  if (Position().Y() + 2 * radius > screenWidth - margin - paddleWidth)
    state.crash = "TMP ball y parst human";
}
