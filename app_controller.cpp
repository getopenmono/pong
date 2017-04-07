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
  state.msBedTime = msInactivityTimeout;
  timer.setCallback(this, &AppController::mainLoop);
  timer.Start();
}

void AppController::computerLoosesOne()
{
  state.reset();
}

void AppController::humanLosesOne()
{
  state.reset();
}

void AppController::mainLoop ()
{
  sendDebugInfo();
  scheduler.run(state);
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
      if (state.computerHasBall)
        state.game = SharedState::GameOn;
      break;
    case SharedState::GameOn:
      if (state.computerMissedBall)
        computerLoosesOne();
      else if (state.humanMissedBall)
        humanLosesOne();
      break;
    case SharedState::Sleep:
      break;
    case SharedState::Crashed:
      break;
  }
  state.msNow += msResolution;
}

void AppController::sendDebugInfo ()
{
  static SharedState oldState;
  if (oldState != state)
  {
    if (state.crash != 0)
    {
      debugLine(state.crash);
      state.game = SharedState::Crashed;
    }
    else
      debugLine(String::Format("state=%d sleep=%d ready=%d computer=%d,%d human=%d,%d ",
        state.game, state.msBedTime, state.humanReady, state.computerHasBall,
        state.computerMissedBall, state.humanHasBall, state.humanMissedBall
      ));
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
  state.game = SharedState::Sleep;
  scheduler.run(state);
}

void AppController::monoWakeFromSleep ()
{
  resetGame();
}
