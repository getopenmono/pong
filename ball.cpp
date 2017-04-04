// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "ball.hpp"

using mono::geo::Point;
using mono::geo::Rect;
using mono::geo::Circle;
using mono::display::Color;

#define radius 5
#define green Color(0,48,0)
#define black mono::display::BlackColor

Ball::Ball (Point const & center_)
:
  View(Rect(center_.X() - radius, center_.Y() - radius, center_.X() + radius, center_.Y() + radius)),
  center(center_)
{
}

void Ball::repaint ()
{
  // painter.useAntialiasedDrawing();
  painter.setBackgroundColor(black);
  painter.drawFillRect(ViewRect(), true);
  painter.setForegroundColor(green);
  painter.drawFillRect(ViewRect().X(), ViewRect().Y(), radius * 2 , radius * 2);
}
