// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "human.hpp"
#include "constants.hpp"

using mono::geo::Rect;
using mono::geo::Circle;
using mono::display::Color;

Human::Human (Rect const & rectangle)
:
  View(rectangle)
{
}

void Human::repaint ()
{
  painter.setBackgroundColor(green);
  painter.drawFillRect(ViewRect(), true);
}

void Human::tick (SharedState & state)
{
  switch (state.game)
  {
    case SharedState::Reset:
      return;
    case SharedState::WaitingForPlayersToReturnToCenter:
      return;
    case SharedState::Sleep:
      return;
  }
}
