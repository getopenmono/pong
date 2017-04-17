// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "ball.hpp"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

Ball::Ball ()
:
  View(Rect(0, 0, 2 * radius, 2 * radius)),
  buzzer(*mono::IApplicationContext::Instance->Buzzer)
{
}

void Ball::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Init:
      xThou = (screenHeight/2 - radius) << 10;
      yThou = (screenWidth/2 - radius) << 10;
      xThouDirection = 0;
      yThouDirection = 0;
      moveBallTo(state.ballX);
      return;
    case SharedState::ComputerServe:
      xThou = (screenHeight/2 - radius) << 10;
      yThou = (screenWidth/2 - radius) << 10;
      xThouDirection = 0;
      yThouDirection = -1024;
      moveBallTo(state.ballX);
      state.nextGameState = SharedState::GameOn;
      return;
    case SharedState::HumanServe:
      xThou = (screenHeight/2 - radius) << 10;
      yThou = (screenWidth/2 - radius) << 10;
      xThouDirection = 0;
      yThouDirection = 1024;
      moveBallTo(state.ballX);
      state.nextGameState = SharedState::GameOn;
      return;
    case SharedState::GameOn:
      stepBall(state);
      return;
    case SharedState::ComputerMissed:
      xThou = (screenHeight/2 - radius) << 10;
      yThou = (screenWidth/2 - radius) << 10;
      xThouDirection = 0;
      yThouDirection = 0;
      moveBallTo(state.ballX);
      return;
    case SharedState::HumanMissed:
      xThou = (screenHeight/2 - radius) << 10;
      yThou = (screenWidth/2 - radius) << 10;
      xThouDirection = 0;
      yThouDirection = 0;
      moveBallTo(state.ballX);
      return;
    case SharedState::Intermission:
      stepBall(state);
      return;
    case SharedState::GameEnd:
      return;
  }
}

void Ball::stepBall (SharedState & state)
{
  if (state.msNow % ballSlowdown != 0)
    return;
  // TODO
  Point corner = calculateNextPosition(state.computerX, state.humanX);
  if (corner.X() != Position().X() || corner.Y() != Position().Y())
    moveBallTo(state.ballX);
  if (corner.Y() == 0)
  {
    state.nextGameState = SharedState::ComputerMissed;
    buzzer.buzzAsync(2);
  }
  else if (corner.Y() == screenWidth - 2 * radius)
  {
    state.nextGameState = SharedState::HumanMissed;
    buzzer.buzzAsync(2);
  }

  if (Position().X() < 0)
    state.crash = "ball x negative";
  if (Position().X() + 2 * radius > screenHeight)
    state.crash = "ball x too high";
  if (Position().Y() < 0)
    state.crash = "ball y negative";
  if (Position().Y() + 2 * radius > screenWidth)
    state.crash = "ball y too high";
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

void Ball::moveBallTo (uint16_t & x)
{
  erase();
  setPosition(Point(xThou >> 10, yThou >> 10));
  repaint();
  x = xThou >> 10;
}

Point Ball::calculateNextPosition (uint16_t computerX, uint16_t humanX)
{
  int x = Position().X();
  int y = Position().Y();
  int xCenter = x + radius;
  int yBottom = y + 2 * radius;

  /* To keep a constant speed of the ball, we need to make sure that the length
     of the vector (xDirection,yDirection) is constant.  To do that without
     floating point calculation, use the following table.

           |      | angle
      -----+------+------
      1024 |    0 |  0
      1020 |   89 |  5
      1008 |  178 | 10
       989 |  265 | 15
       962 |  350 | 20
       928 |  433 | 25
       887 |  512 | 30
       839 |  587 | 35
       784 |  658 | 40
       724 |  724 | 45
   */

  // Computer hit?
  if (y <= margin + paddleWidth)
  {
    // Half of ball must be on paddle for hit.
    if (xCenter > computerX && xCenter < computerX + paddleLength)
    {
      buzzer.buzzAsync(1);
      // Bounce back.
      // At an angle proportional to distance to center of paddle.
      if (x < computerX)
      {
        xThouDirection = -887;
        yThouDirection = 512;
      }
      else if (xCenter + radius > computerX + paddleLength)
      {
        xThouDirection = 887;
        yThouDirection = 512;
      }
      else if (xCenter < computerX + paddleLength / 4)
      {
        xThouDirection = -724;
        yThouDirection = 724;
      }
      else if (xCenter > computerX + paddleLength / 2 + paddleLength / 4)
      {
        xThouDirection = 724;
        yThouDirection = 724;
      }
      else
      {
        xThouDirection = 0;
        yThouDirection = 724;
      }
    }
  }
  // Human hit?
  else if (yBottom >= screenWidth - margin - paddleWidth)
  {
    // Half of ball must be on paddle for hit.
    if (xCenter > humanX && xCenter < humanX + paddleLength)
    {
      buzzer.buzzAsync(1);
      // Bounce back.
      // At an angle proportional to distance to center of paddle.
      if (x < humanX)
      {
        xThouDirection = -887;
        yThouDirection = -512;
      }
      else if (xCenter + radius > humanX + paddleLength)
      {
        xThouDirection = 887;
        yThouDirection = -512;
      }
      else if (x < humanX + paddleLength / 3)
      {
        xThouDirection = -724;
        yThouDirection = -724;
      }
      else if (xCenter + radius > humanX + paddleLength / 3 + paddleLength / 3)
      {
        xThouDirection = 724;
        yThouDirection = -724;
      }
      else
      {
        xThouDirection = 0;
        yThouDirection = -1024;
      }
    }
  }
  return effectuateDirection();
}

Point Ball::effectuateDirection ()
{
  xThou += xThouDirection;
  yThou += yThouDirection;
  if (xThou <= 0)
  {
    buzzer.buzzAsync(1);
    xThouDirection = -xThouDirection;
    if (xThou < 0)
      xThou = -xThou;
  }
  else if ((xThou >> 10) + 2*radius >= screenHeight)
  {
    buzzer.buzzAsync(1);
    xThouDirection = -xThouDirection;
    if ((xThou >> 10) + 2*radius >= screenHeight)
      xThou = ((2*(screenHeight - 2*radius)) << 10) - xThou;
  }
  return Point(xThou >> 10, yThou >> 10);
}
