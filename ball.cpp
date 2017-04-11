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
  reset();
  xDirection = 0;
  yDirection = 0;
}

void Ball::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Intermission:
      return;
    case SharedState::ComputerServe:
      reset();
      xDirection = 0;
      yDirection = -1;
      break;
    case SharedState::HumanServe:
      reset();
      xDirection = 0;
      yDirection = 1;
      break;
    case SharedState::GameOn:
      break;
    case SharedState::UpdateScore:
      return;
    case SharedState::GameEnd:
      return;
  }
  if (state.msNow % ballSlowdown != 0)
    return;
  Point corner = calculateNextPosition(state.computerX, state.humanX);
  if (corner.X() != Position().X() || corner.Y() != Position().Y())
    moveBallTo(corner, state.ballX);
  if (corner.Y() == 0)
    state.computerMissed = true;
  else if (corner.Y() == screenWidth - 2 * radius)
    state.humanMissed = true;

  if (Position().X() < 0)
    state.crash = "ball x negative";
  if (Position().X() + 2 * radius > screenHeight)
    state.crash = "ball x too high";
  if (Position().Y() < 0)
    state.crash = "ball y negative";
  if (Position().Y() + 2 * radius > screenWidth)
    state.crash = "ball y too high";
}

void Ball::reset ()
{
  setPosition(Point(screenHeight/2 - radius, screenWidth/2 - radius));
}

void Ball::erase ()
{
  painter.setForegroundColor(black);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2, radius * 2);
}

void Ball::repaint ()
{
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2, radius * 2);
}

void Ball::moveBallTo (Point position, uint16_t & x)
{
  erase();
  setPosition(position);
  repaint();
  x = position.X();
}

Point Ball::calculateNextPosition (uint16_t computerX, uint16_t humanX)
{
  int x = Position().X();
  int y = Position().Y();
  int xCenter = x + radius;
  int yBottom = y + 2 * radius;
  // Computer hit?
  if (y <= margin + paddleWidth)
  {
    // Half of ball must be on paddle for hit.
    if (xCenter > computerX && xCenter < computerX + paddleLength)
    {
      // Bounce back.
      yDirection = 1;
      // At an angle proportional to distance to center of paddle.
      if (x < computerX)
        xDirection = -2;
      else if (xCenter + radius > computerX + paddleLength)
        xDirection = 2;
      else if (xCenter < computerX + paddleLength / 4)
        xDirection = -1;
      else if (xCenter > computerX + paddleLength / 2 + paddleLength / 4)
        xDirection = 1;
      else
        xDirection = 0;
    }
  }
  // Human hit?
  else if (yBottom >= screenWidth - margin - paddleWidth)
  {
    // Half of ball must be on paddle for hit.
    if (xCenter > humanX && xCenter < humanX + paddleLength)
    {
      // Bounce back.
      yDirection = -1;
      // At an angle proportional to distance to center of paddle.
      if (x < humanX)
        xDirection = -2;
      else if (xCenter + radius > humanX + paddleLength)
        xDirection = 2;
      else if (x < humanX + paddleLength / 3)
        xDirection = -1;
      else if (xCenter + radius > humanX + paddleLength / 3 + paddleLength / 3)
        xDirection = 1;
      else
        xDirection = 0;
    }
  }
  return effectuateDirection();
}

Point Ball::effectuateDirection ()
{
  int x = Position().X() + xDirection;
  int y = Position().Y() + yDirection;
  if (x <= 0)
  {
    xDirection = 1;
    if (x < 0)
      x = -x;
  }
  else if (x + 2 * radius >= screenHeight)
  {
    xDirection = -1;
    if (x  + 2 * radius > screenHeight)
      x = screenHeight-x;
  }
  return Point(x, y);
}

