//
// Follow: move a circle towards a target using easing movement calculations.
// Click the mouse to set a new target location.
//
// 2016 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);

		float posX, posY; // position
		float easing; // easing percentage
	
		// target to move toward
		float targetX, targetY;
};
