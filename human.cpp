// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "human.hpp"
#include "constants.hpp"

using mono::geo::Rect;
using mono::geo::Point;
using mono::geo::Circle;
using mono::display::Color;

Human::Human ()
:
  View(Rect(0, 0, paddleLength, paddleWidth))
{
  lastPulses = 0;
  setPosition(Point(0, screenWidth-paddleWidth-margin));
}

void Human::tick (SharedState & state)
{
  if (computerPlaysForHuman)
    followBall(state.ballX);
  else
    followEncoder(state.encoderPulses);
  state.humanX = Position().X();

  if (Position().X() < 0)
    state.crash = "human x negative";
  if (Position().X() + paddleLength > screenHeight)
    state.crash = "human x too high";
}

void Human::reset (int encoderPulses)
{
  erase();
}

void Human::erase ()
{
  painter.setBackgroundColor(black);
  painter.drawFillRect(ViewRect(), true);
}

void Human::repaint ()
{
  painter.setBackgroundColor(green);
  painter.drawFillRect(ViewRect(), true);
}

bool Human::paddleCoversCenter ()
{
  uint16_t x = Position().X();
  uint16_t middle = screenHeight / 2;
  return (x < middle && x + paddleLength > middle);
}

bool Human::calculateHasBall (uint16_t ballX, uint16_t ballY)
{
  int y = Position().Y();
  if (y <= ballY + 2 * radius)
  {
    int x = Position().X();
    if (x <= ballX && (ballX + 2 * radius) <= (x + paddleLength))
      return true;
  }
  return false;
}

void Human::followBall (uint16_t ballX)
{
  if (rng.random31b() % 3 == 0)
    return;
  int x = Position().X();
  int direction = ballX - (x + paddleLength/2);
  if (direction < 0)
    x -= 1;
  else if (direction > 0)
    x += 1;
  if (x < 0)
    x = 0;
  else if (x > screenHeight - paddleLength)
    x = screenHeight - paddleLength;
  if (x != Position().X())
  {
    erase();
    setPosition(Point(x, Position().Y()));
    repaint();
  }
}

void Human::followEncoder (int encoderPulses)
{
  int const direction = lastPulses - encoderPulses;
  int oldX = Position().X();
  int x = oldX + direction * pulsesPerPixel;
  if (x < 0)
    x = 0;
  if (x > screenHeight - paddleLength)
    x = screenHeight - paddleLength;
  if (x != oldX)
  {
    erase();
    setPosition(Point(x, Position().Y()));
    repaint();
  }
  lastPulses = encoderPulses;
}
