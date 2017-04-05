// Draw: simple drawing program using the mouse and keyboard
//
// Click and drag to draw lines. Press the 1, 2, 3 or 0 keys to change colors.
//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		// line color when drawing
		ofColor lineColor = ofColor::black;
	
		// line width when drawing
		int lineWidth = 1;
	
		ofPoint mouse; // current mouse pos
		ofPoint pmouse; // previous mouse pos
};
