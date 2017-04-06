// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "app_controller.h"
#include "constants.hpp"

using mono::geo::Point;
using mono::geo::Rect;

AppController::AppController ()
:
  player(Rect(50, 220-paddleWidth-margin, paddleLength, paddleWidth)),
  computer(Rect(100, 0+margin, paddleLength, paddleWidth)),
  timer(msResolution)
{
  scheduler.add(&ball);
  scheduler.add(&player);
  scheduler.add(&computer);
  scheduler.add(&joystick);
}

void AppController::resetGame ()
{
  state.game = SharedState::Reset;
  state.msNow = 0;
  state.msBedTime = msInactivityTimeout;
  scheduler.run(state);
  timer.setCallback(this, &AppController::mainLoop);
  timer.Start();
}

void AppController::mainLoop ()
{
  state.msNow += msResolution;
  if (state.msBedTime == state.msNow)
    return mono::IApplicationContext::EnterSleepMode();
  switch (state.game)
  {
    case SharedState::Reset:
      state.game = SharedState::WaitingForPlayersToReturnToCenter;
      return;
    case SharedState::WaitingForPlayersToReturnToCenter:
      return;
    case SharedState::Sleep:
      return;
  }
  scheduler.run(state);
}

void AppController::monoWakeFromReset ()
{
  resetGame();
}

void AppController::monoWillGotoSleep ()
{
  // timer.Stop();  TODO: Is this necessary?
  state.game = SharedState::Sleep;
  scheduler.run(state);
}

void AppController::monoWakeFromSleep ()
{
  resetGame();
}
