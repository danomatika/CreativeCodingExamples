//
// Brightest: search for brightest pixel in camera frames
//
// 2017 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"
#include "MovingAverage.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	
		// grab camera frames
		ofVideoGrabber grabber;
	
		// brightest pos using a moving average for smoothing
		ofxMovingAverage x, y;
	
		// brightness path line consisting of prev 100 points
		ofPolyline line;
};
