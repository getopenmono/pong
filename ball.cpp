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
      thouX = (screenHeight/2 - radius) << 10;
      thouY = (screenWidth/2 - radius) << 10;
      thouXDirection = 0;
      thouYDirection = 0;
      moveBallTo(state.ballX);
      return;
    case SharedState::ComputerServe:
      thouX = (screenHeight/2 - radius) << 10;
      thouY = (screenWidth/2 - radius) << 10;
      thouXDirection = 0;
      thouYDirection = -1024;
      moveBallTo(state.ballX);
      state.nextGameState = SharedState::GameOn;
      return;
    case SharedState::HumanServe:
      thouX = (screenHeight/2 - radius) << 10;
      thouY = (screenWidth/2 - radius) << 10;
      thouXDirection = 0;
      thouYDirection = 1024;
      moveBallTo(state.ballX);
      state.nextGameState = SharedState::GameOn;
      return;
    case SharedState::GameOn:
      stepBall(state);
      return;
    case SharedState::ComputerMissed:
      thouX = (screenHeight/2 - radius) << 10;
      thouY = (screenWidth/2 - radius) << 10;
      thouXDirection = 0;
      thouYDirection = 0;
      moveBallTo(state.ballX);
      return;
    case SharedState::HumanMissed:
      thouX = (screenHeight/2 - radius) << 10;
      thouY = (screenWidth/2 - radius) << 10;
      thouXDirection = 0;
      thouYDirection = 0;
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
  Point corner = calculateNextPosition(state.computerX, state.humanX);
  //if ((corner.X() >> 10) != Position().X() || (corner.Y() >> 10) != Position().Y())
    moveBallTo(state.ballX);
  if ((corner.Y() >> 10) == 0)
  {
    state.nextGameState = SharedState::ComputerMissed;
    buzzer.buzzAsync(2);
  }
  else if ((corner.Y() >> 10) == screenWidth - 2 * radius)
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
  erase();
  setPosition(Point(thouX >> 10, thouY >> 10));
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2, radius * 2);
}

void Ball::moveBallTo (uint16_t & x)
{
  scheduleRepaint();
  x = thouX >> 10;
}

Point Ball::calculateNextPosition (uint16_t computerX, uint16_t humanX)
{
  int x = thouX >> 10;
  int y = thouY >> 10;
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
        thouXDirection = -887;
        thouYDirection = 512;
      }
      else if (xCenter + radius > computerX + paddleLength)
      {
        thouXDirection = 887;
        thouYDirection = 512;
      }
      else if (xCenter < computerX + paddleLength / 3)
      {
        thouXDirection = -724;
        thouYDirection = 724;
      }
      else if (xCenter > computerX + paddleLength / 3 + paddleLength / 3)
      {
        thouXDirection = 724;
        thouYDirection = 724;
      }
      else
      {
        thouXDirection = 0;
        thouYDirection = 724;
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
        thouXDirection = -887;
        thouYDirection = -512;
      }
      else if (xCenter + radius > humanX + paddleLength)
      {
        thouXDirection = 887;
        thouYDirection = -512;
      }
      else if (x < humanX + paddleLength / 3)
      {
        thouXDirection = -724;
        thouYDirection = -724;
      }
      else if (xCenter + radius > humanX + paddleLength / 3 + paddleLength / 3)
      {
        thouXDirection = 724;
        thouYDirection = -724;
      }
      else
      {
        thouXDirection = 0;
        thouYDirection = -1024;
      }
    }
  }
  return effectuateDirection();
}

Point Ball::effectuateDirection ()
{
  thouX += thouXDirection;
  thouY += thouYDirection;
  if (thouX <= 0)
  {
    buzzer.buzzAsync(1);
    thouXDirection = -thouXDirection;
    if (thouX < 0)
      thouX = -thouX;
  }
  else if ((thouX >> 10) + 2*radius >= screenHeight)
  {
    buzzer.buzzAsync(1);
    thouXDirection = -thouXDirection;
    if ((thouX >> 10) + 2*radius >= screenHeight)
      thouX = ((2*(screenHeight - 2*radius)) << 10) - thouX;
  }
  return Point(thouX, thouY);
}
