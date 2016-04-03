//
// Millis: simple animation timing using the number of elapse milliseconds since
// the program started.
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

		void mouseMoved(int x, int y );
	
		// flashing red circle
		float redX, redY; // position
		long redMillis; // animation timestamp
		bool showRed; // draw the red circle?
	
		// shy green circle, only moves towards the mouse if the mouse is
		// not moving
		float greenX, greenY; // position
		long greenMillis; // animation timestamp
		bool moveGreen; // move towards the mouse?
	
};
