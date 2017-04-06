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

void Human::reset ()
{
  setPosition(Point(50, screenWidth-paddleWidth-margin));
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

void Human::tick (SharedState & state)
{
  static int lastPulses = 0;
  switch (state.game)
  {
    case SharedState::Reset:
      return reset();
    case SharedState::WaitingForPlayersToReturnToCenter:
      // if (position near center and some movement has been made) change state
      break;
    case SharedState::Sleep:
      return;
  }
  erase();
  int const direction = state.encoderPulses - lastPulses;
  lastPulses = state.encoderPulses;
  int x = Position().X() + direction * pulsesPerPixel;
  if (x < 0)
    x = 0;
  if (x > screenHeight - paddleLength)
    x = screenHeight - paddleLength;
  setPosition(Point(x, Position().Y()));
}
