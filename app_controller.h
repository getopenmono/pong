// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef app_controller_h
#define app_controller_h
#include <mono.h>
#include "shared-state.hpp"
#include "ball.hpp"
#include "computer.hpp"
#include "human.hpp"
#include "encoder.hpp"
#include "scheduler.hpp"

class AppController
:
  public mono::IApplication
{
  SharedState state;
  Scheduler scheduler;
  Ball ball;
  Human player;
  Encoder joystick;
  Computer computer;
  mono::Timer timer;
  void resetGame ();
  void mainLoop ();
  void sendDebugInfo ();
  void debugLine (mono::String msg);
public:
  AppController ();
  void monoWakeFromReset ();
  void monoWillGotoSleep ();
  void monoWakeFromSleep ();
};

#endif // app_controller_h
