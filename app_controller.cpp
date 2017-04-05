// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "app_controller.h"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

AppController::AppController ()
:
  ball(Point(176/2, 220/2)),
  player(Rect(50, 220-paddleWidth-margin, paddleLength, paddleWidth)),
  computer(Rect(100, 0+margin, paddleLength, paddleWidth))
{
  scheduler.add(&ball);
  scheduler.add(&player);
  scheduler.add(&computer);
}

void AppController::monoWakeFromReset ()
{
  scheduler.run(state);
}

void AppController::monoWillGotoSleep ()
{
}

void AppController::monoWakeFromSleep ()
{
  monoWakeFromReset();
}
