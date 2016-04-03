//
// Bounce: bounce a circle (or rectangle) around the screen. Demonstrates
// simple linear motion with direction & velocity (aka speed). Click the
// mouse to choose a new position and random velocity. 
//
// 2016 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
	
		// main callbacks
		void setup();
		void update();
		void draw();
	
		void mousePressed(int x, int y, int button);
	
		// other interaction callbacks removed since
		// we don't need them for this example
	
		// position
		float posX, posY;
	
		// velocity
		float velX, velY;
	
		// how big?
		float size;
	
		// draw a circle or a rectangle?
		bool isCircle;
};
