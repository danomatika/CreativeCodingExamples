//
// SinCos: movement animation using the sine & cosine functions. The trig
// functions (sin, cos, & tan) return values from -1 to 1 and are useful as
// multiplication modifiers:
//
// ie. to oscillate around a desired value:
//
//     newValue = sin(angle) * desiredValue
//     angle = angle + step
//
// angle is the current angle position in radians used in the trig function.
// step is how much to add to the angle each frame which basically controls the
// speed.
//
// For sin, these angle positions range:
//
//  * 0     - pi/2  ->  0 -  1 (positive, rising)
//  * pi/2  - pi    ->  1 -  0 (positive, falling)
//  * pi    - 3pi/2 ->  0 - -1 (negative, falling)
//  * 3pi/2 - 2pi   -> -1 -  0 (negative, rising)
//
// and so on above & below into infinity (!)
//
// openFrameworks includes several constants which define commonly used radian
// values: HALF_PI, PI, TWO_PI, FOUR_PI. You can use them in place of numbers
// when doing math or making comparisons:
//
//     if(angle > TWO_PI) {
//	       angle = PI;
//     }
//
// Sometimes you don't want the sin value from -1 to 1, but instead only 0 to 1.
// In this case, you can simple use the absolute value of the sin value:
//
//     newValue = abs(sin(angle)) * desiredValue;
//
// Other times, you may want to use just a section of the sin function to animate
// a rising or falling value, say move from 0 to a desired value and stop. In
// this case, you want the values of sin from 0 - HALF_PI (rising):
//
//     newValue = sin(angle) * desiredValue;
//     if(angle < HALF_PI) {
//	       angle = angle + step
//     }
//
// This will keep updating the angle (and animating) while less than HALF_PI,
// but will stop updating once HALF_PI is reached. To restart the animation,
// just reset angle to 0.
//
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
	
		// green circle, moves horizontally across the window using sin
		float greenPosX, greenPosY;
		float greenBaseX; // base position
		float greenOffsetX; // how far to move +/- from the base pos
		float greenAngleX; // sin angle animation variables
	
		// red circle, rotates around the center of the window using sin & cos
		float redPosX, redPosY;
		float redBaseX, redBaseY; // base position
		float redOffsetX, redOffsetY; // how far to move +/- from the base pos
		float redAngleX, redAngleY; // sin/cos angle animation variables
	
		// blue circle, moves from the top of the window to the bottom and
		// back using sin when the spacebar is pressed
		float bluePosX, bluePosY;
		float blueBaseY; // base position
		float blueOffsetY; // how far to move +/- from the base pos
		float blueAngleY; // sin/cos angle animation variables
		float blueAngleStep; // how much to add to the angle each frame
	
		// yellow circle, moves from left to right & "bounces" on the bottom of
		// the window when the mouse button is pressed
		float yellowPosX, yellowPosY;
		float yellowBaseY;
		float yellowOffsetY;
		float yellowAngleY;
		float yellowAngleStep;
		float yellowVelX; // linear horz velocity
};
