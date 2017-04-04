// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "app_controller.h"

using mono::geo::Point;
using mono::geo::Rect;

#define margin 3
#define paddleWidth 5
#define paddleLength 50

AppController::AppController()
:
  ball(Point(176/2, 220/2)),
  player(Rect(50, 220-paddleWidth-margin, paddleLength, paddleWidth)),
  computer(Rect(100, 0+margin, paddleLength, paddleWidth))
{
}

void AppController::monoWakeFromReset ()
{
  ball.show();
  player.show();
  computer.show();
}

void AppController::monoWillGotoSleep ()
{
}

void AppController::monoWakeFromSleep ()
{
}
