//
// DrawOsc: Draw on each other's screen using
// OSC (Open Sound Control. Requires the ofxOsc addon.
//
// 2017 Dan Wilcox
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
	
		ofxOscSender sender;
		ofxOscReceiver receiver;
	
		bool print = false; // print received message?
	
		// remote mouse info
		int remoteMouseX = 0;
		int remoteMouseY = 0;
		int remoteMouseButton = 0;
		bool remoteMousePressed = false;
};
