// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_constants_h
#define pong_constants_h
#include <mono.h>

using mono::display::Color;

/**
 * These are the settings that control the layout of the game.
 * Values without units are number of pixels.
 */

#define computerPlaysForHuman false
#define msResolution 1
#define ballSlowdown 5
#define computerSlowdown 6
#define margin 3
#define paddleWidth 5
#define paddleLength 50
#define radius 5
#define green Color(0,63,0)
#define black mono::display::BlackColor
#define pulsesPerPixel 3
#define msIntermission 2000
#define msInactivityTimeout 60000
#define digitWidth 5

// Hardware constants.

#define screenWidth 220
#define screenHeight 176

#endif // pong_constants_h
