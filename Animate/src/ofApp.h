// Animate: playback an animation by loading and displaying individual frames
//
// Mouse X pos controls playback speed.
//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

// our custom Animation class
#include "Animation.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
	
		// the animation
		Animation nyan;
};
