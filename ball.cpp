// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "ball.hpp"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;
using mono::geo::Circle;
using mono::display::Color;

Ball::Ball ()
:
  View(Rect(0, 0, 2 * radius, 2 * radius)),
  center(0, 0)
{
}

void Ball::reset ()
{
  center.setX(screenHeight/2);
  center.setY(screenWidth/2);
  setPosition(Point(center.X() - radius, center.Y() - radius));
}

void Ball::repaint ()
{
  // painter.useAntialiasedDrawing();
  painter.setBackgroundColor(black);
  painter.drawFillRect(ViewRect(), true);
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2 , radius * 2);
}

void Ball::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Reset:
      return reset();
    case SharedState::WaitingForPlayersToReturnToCenter:
      return;
    case SharedState::Sleep:
      return;
  }
}
