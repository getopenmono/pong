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
  erase();
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

Point Ball::calculateNextPosition (uint16_t computerX, uint16_t humanX)
{
  int x = Position().X();
  int y = Position().Y();
  int xCenter = x + radius;
  int yBottom = y + 2 * radius;
  // Computer hit?
  if (y <= margin + paddleWidth)
  {
    printf("Top %d vs %d\r\n", xCenter, computerX);
    // Half of ball must be on paddle for hit.
    if (xCenter > computerX && xCenter < computerX + paddleLength)
    {
      printf("Computer Hit\r\n");
      // Bounce back.
      yDirection = ballSpeed;
      // At an angle proportional to distance to center of paddle.
      if (x < computerX)
        xDirection = -2 * ballSpeed;
      else if (xCenter + radius > computerX + paddleLength)
        xDirection = 2 * ballSpeed;
      else if (x < computerX + paddleLength / 3)
        xDirection = -ballSpeed;
      else if (xCenter + radius > computerX + paddleLength / 3 + paddleLength / 3)
        xDirection = ballSpeed;
      else
        xDirection = 0;
      printf("xDirection = %d\r\n", xDirection);
    }
  }
  // Human hit?
  else if (yBottom >= screenWidth - margin - paddleWidth)
  {
    printf("Bottom %d vs %d\r\n", xCenter, humanX);
    // Half of ball must be on paddle for hit.
    if (xCenter > humanX && xCenter < humanX + paddleLength)
    {
      printf("Human Hit\r\n");
      // Bounce back.
      yDirection = -ballSpeed;
      // At an angle proportional to distance to center of paddle.
      if (x < humanX)
        xDirection = -2 * ballSpeed;
      else if (xCenter + radius > humanX + paddleLength)
        xDirection = 2 * ballSpeed;
      else if (x < humanX + paddleLength / 3)
        xDirection = -ballSpeed;
      else if (xCenter + radius > humanX + paddleLength / 3 + paddleLength / 3)
        xDirection = ballSpeed;
      else
        xDirection = 0;
      printf("xDirection = %d\r\n", xDirection);
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
      break;
    case SharedState::Sleep:
      return;
    case SharedState::Crashed:
      return;
  }
  Point corner = calculateNextPosition(state.computerX, state.humanX);
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
}
