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
  state.msNow += msResolution;
  // Testing delay.
  if (state.msNow < 1000)
    return;
  sendDebugInfo();
  scheduler.run(state);
}

void AppController::sendDebugInfo ()
{
  static SharedState lastState;
  if (state != lastState)
  {
    debugLine(String::Format(
      "game=%d, next=%d, ball=%d, computer=%d, human=%d, encoder=%d %s",
      state.game,
      state.nextGameState,
      state.ballX,
      state.computerX,
      state.humanX,
      state.encoderPulses,
      state.crash
    ));
    lastState = state;
  }
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
