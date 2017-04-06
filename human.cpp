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
}

void Human::reset (int encoderPulses)
{
  lastPulses = encoderPulses;
  setPosition(Point(0, screenWidth-paddleWidth-margin));
}

/*
void Human::moveTo (uint16_t x)
{
  uint16_t y = Position().Y();
  uint16_t oldX = Position().X();
  // Erase and paint only non-overlapping parts.
  painter.setBackgroundColor(black);
  if (x > oldX)
  {
    painter.drawFillRect(oldX, y, oldX - x, paddleWidth, true);
    painter.setBackgroundColor(green);
    painter.drawFillRect(oldX + paddleLength, y, oldX - x, paddleWidth, true);
  }
  else if (x < oldX)
  {
    painter.drawFillRect(x + paddleLength, y, oldX - x, paddleWidth, true);
    painter.setBackgroundColor(green);
    painter.drawFillRect(x, y, oldX - x, paddleWidth, true);
  }
  setPosition(Point(x, y));
}
*/

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

void Human::tick (SharedState & state)
{
  static int lastPulses = 0;
  switch (state.game)
  {
    case SharedState::Reset:
      reset(state.encoderPulses);
      repaint();
      return;
    case SharedState::WaitingForHumanToReturnToCenter:
      break;
    case SharedState::ComputerToServe:
      break;
    case SharedState::GameOn:
      break;
    case SharedState::Sleep:
      return;
  }
  int const direction = state.encoderPulses - lastPulses;
  lastPulses = state.encoderPulses;
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
  state.humanReady = paddleCoversCenter();
}
