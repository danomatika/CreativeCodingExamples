//
// Gravity: simulate gravity to bounce a circle using vector math for velocity
// and acceleration.
//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
// openFrameworks has a number of mathematical vector objects:
// * ofVec2f - 2 dimensional vector
// * ofVec3f - 3 dimensional vector
// * ofPoint - alias for ofVec3f, *best for general use
// * ofVec4f - 4 dimensional vector
//
// Note: A mathematical vector is *not* the same as a C++ vector. Yeah this can
// be a bit confusing ;)
//
// A math vector (and ofPoint) is basically a container around the individual
// axis position values (x, y, z) and also includes a number of built-in math
// operations to make life easier (addition, subtraction, dist, magnitude, etc).
//
// You can also use normal math operators on them:
//
//    ofPoint pos(100, 100);
//    ofPoint vel(-4, 4);
//
//    // update the pos using the vel
//    pos = pos + vel;
//
// Some math vector references:
//  * ofBook: Math from 1d to 4d: http://openframeworks.cc/ofBook/chapters/math.html
//  * Vector Maths in Unity: https://www.youtube.com/watch?v=7DK8aA2qee8
//  * Processing Vector tutorial: https://processing.org/tutorials/pvector
//
// Note: Unity uses the base OpenGL coordinate system which has the origin (0,0)
// in the lower right corner of the window. Processing and OF have the origin
// in the upper left corner so keep that in mind when watching the Unity video.
//
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		ofPoint pos; // circle position
		ofPoint vel; // circle velocity
		ofPoint acc; // circle acceleration
		float size;  // circle size
	
		ofPoint gravity; // acceleration due to gravity, in this case downward
		float damping; // percentage modifier applied when the circle bounces
	
		bool dragging; // mouse being dragged? (aka moved when button down)
		ofPoint pressed; // mouse position when pressed
};
