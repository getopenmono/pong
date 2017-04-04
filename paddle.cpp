// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "paddle.hpp"

using mono::geo::Rect;
using mono::geo::Circle;
using mono::display::Color;

#define radius 5
#define green Color(0,48,0)
#define black mono::display::BlackColor

Paddle::Paddle (Rect const & rectangle)
:
  View(rectangle)
{
}

void Paddle::repaint ()
{
  painter.setBackgroundColor(green);
  painter.drawFillRect(ViewRect(), true);
}
