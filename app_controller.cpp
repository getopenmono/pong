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
      state.game = SharedState::WaitingForHumanToReturnToCenter;
      break;
    case SharedState::WaitingForHumanToReturnToCenter:
      if (state.humanReady)
        state.game = SharedState::ComputerToServe;
      break;
    case SharedState::ComputerToServe:
      break;
    case SharedState::Sleep:
      break;
  }
  sendDebugInfo();
  scheduler.run(state);
}

void AppController::sendDebugInfo ()
{
  static SharedState oldState;
  if (oldState != state)
  {
    debugLine(String::Format("state=%d, sleep=%d, pulses=%d, ready=%d ball=%d ms=%d",
      state.game, state.msBedTime, state.encoderPulses, state.humanReady, state.ballX, state.msNow));
  }
  oldState = state;
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
  // timer.Stop();  TODO: Is this necessary?
  state.game = SharedState::Sleep;
  scheduler.run(state);
}

void AppController::monoWakeFromSleep ()
{
  resetGame();
}
