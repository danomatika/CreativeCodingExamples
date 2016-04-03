//
// Easing: move circles horizontally towards a target x position using an
// easing calculation. Press a mouse button to reset.
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
	
		// interaction callbacks
		void mousePressed(int x, int y, int button);
	
		// red circle
		float redX, redY; // position
		float redEasing; // easing percentage

		// green circle
		float greenX, greenY;
		float greenEasing;
	
		// blue circle
		float blueX, blueY;
		float blueEasing;
	
		// target position to move to
		float targetX;
};
