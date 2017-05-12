//
// 2017 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Brightest");
	ofBackground(255);

	// set up camera to grab at 640x480,
	// smaller sizes are faster as there are less pixels to process
	grabber.setup(640, 480);

	// set window size to adjust smooth (more) vs responsiveness (less)
	x.setSize(50);
	y.setSize(50);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	// check if there are new camera frames & update pixels if there are
	grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// draw the camera frame
	ofSetColor(255);
	grabber.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	float maxBrightness = 0; // max brightness found when comparing
	ofPoint brightest; // position of the current brightest pixel found
	
	// check each pixel and look for the brightest
	ofPixels &pixels = grabber.getPixels(); // pixel data ref
	for(int y = 0; y < pixels.getHeight(); y = y + 1) {
		for(int x = 0; x < pixels.getWidth(); x = x + 1) {
			ofColor c = pixels.getColor(x, y);
			
			// compare this pixel's color to see if it's the
			// current brightest pixel, if so update the brightest pos
			if(c.getBrightness() > maxBrightness) {
				maxBrightness = c.getBrightness();
				brightest.set(x, y);
			}
		}
	}
	
	// scale brightest pixel position from range within grabber image
	// to range on the screen
	x = ofMap(brightest.x, 0, grabber.getWidth(), 0, ofGetWidth());
	y = ofMap(brightest.y, 0, grabber.getHeight(), 0, ofGetHeight());
	
	// add brightest pos to line
	line.addVertex(x, y);
	while(line.size() > 100) {
		// pop front until we are under 100 items
		line.getVertices().erase(line.begin());
	}
	
	// draw the line shape
	ofSetColor(0, 255, 255);
	ofSetLineWidth(5);
	line.draw();
	
	// draw the current brightest point
	ofSetColor(255, 0, 255);
	ofFill();
	ofDrawCircle(x, y, 10);
}
