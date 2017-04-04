// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef app_controller_h
#define app_controller_h
#include <mono.h>
#include <ball.hpp>
#include <paddle.hpp>

class AppController : public mono::IApplication
{
  Ball ball;
  Paddle player;
  Paddle computer;
public:
  AppController ();
  void monoWakeFromReset ();
  void monoWillGotoSleep ();
  void monoWakeFromSleep ();
};

#endif // app_controller_h
