// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "app_controller.h"
#include "constants.hpp"

using mono::String;

AppController::AppController ()
:
  timer(msResolution)
{
  scheduler.add(&ball);
  scheduler.add(&player);
  scheduler.add(&computer);
  scheduler.add(&joystick);
  scheduler.add(&score);
}

void AppController::resetGame ()
{
  state.reset();
  timer.setCallback(this, &AppController::mainLoop);
  timer.Start();
}

void AppController::mainLoop ()
{
  sendDebugInfo();
  scheduler.run(state);
  state.msNow += msResolution;
}

void AppController::sendDebugInfo ()
{
  if (state.crash != 0)
  {
    debugLine(state.crash);
    state.game = SharedState::GameEnd;
    timer.Stop();
  }
}

void AppController::debugLine (String msg)
{
  printf(String::Format("%s\r\n",msg())());
}

void AppController::monoWakeFromReset ()
{
  resetGame();
}

void AppController::monoWillGotoSleep ()
{
  timer.Stop();
}

void AppController::monoWakeFromSleep ()
{
  resetGame();
}
