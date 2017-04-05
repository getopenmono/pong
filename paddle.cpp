// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "paddle.hpp"
#include "constants.hpp"

using mono::geo::Rect;
using mono::geo::Circle;
using mono::display::Color;

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

void Paddle::tick (SharedState & state)
{
}
