//
// OscEvents: Send & receive mouse & keyboard events over
// OSC (Open Sound Control. Requires the ofxOsc addon.
//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		ofxOscReceiver receiver;
		ofxOscSender sender;
	
		ofTrueTypeFont font;
	
		// received data from OSC
		ofPoint mousePos;
		bool buttonDown;
		int key;
};
