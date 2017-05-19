// Blobs: blob tracking using OpenCV with persistent ids between frames
//
// Persistence algorithm from touchlib and implemented in ofxCvBlobTracker
// by stefanix.
//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"
#include "ofxCvBlobTracker.h"

// inherit from ofxCvBlobListener for recieving blob events
class ofApp : public ofBaseApp, public ofxCvBlobListener{

	public:
	
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);

		// blob event callbacks
		void blobEntered(int x, int y, int id, int order);
		void blobMoved(int x, int y, int id, int order);
		void blobExited(int x, int y, int id, int order);

		ofVideoGrabber grabber;

        ofxCvColorImage colorImg;

        ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage grayBg;
		ofxCvGrayscaleImage grayDiff;

        ofxCvContourFinder contourFinder;
		ofxCvBlobTracker tracker; //< persistent id blob tracker

		int threshold;
		bool learnBackground;
};
