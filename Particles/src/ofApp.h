//
// Particles: a small particle system using a class & pointers to avoid copying.
// Left click with the mouse to add a circle and right click to explode them.
// Circles are removed once they have reached the max number of bounces off
// the window edges.
//
// References:
//  * Stanford CS Pointer Basics: http://cslibrary.stanford.edu/106
//  * ofBook: OOPS!: http://openframeworks.cc/ofBook/chapters/OOPs!.html
//  * ofBook: vector: http://openframeworks.cc/ofBook/chapters/stl_vector.html
//  * http://www.cplusplus.com/reference/vector
//
#pragma once

#include "ofMain.h"

// I want to use the Circle class, so include
// the header so we know about it in ofApp.
#include "Circle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
	
		// vector of circle pointers
		vector<Circle*> circles;
	
		// maximum allowed number of bounces before removing a Circle
		int maxBounces = 4;
};
