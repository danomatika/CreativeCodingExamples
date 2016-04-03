//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(ofColor::darkGray);
	ofSetWindowTitle("Millis");
	ofSetCircleResolution(50);
	
	// red circle
	redX = ofGetWidth()/2;
	redY = ofGetHeight()/2;
	redMillis = 0; // init timestamp
	showRed = false; // don't show yet
	
	// green circle
	greenX = ofRandom(20, ofGetWidth()-20);
	greenY = ofRandom(20, ofGetHeight()-20);
	greenMillis = 0;
	moveGreen = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	// ofGetElapseTimeMillis() returns the number of milliseconds
	// that have occurred since the program was started. It is always
	// increasing, so if we subtract the current red circle timestamp
	// from the current millis, we can see if the last time we did something was
	// greater or less than 1/2 a second ago (500 ms = 0.5s).
	//
	// Using millis also allows you to time animations even if the framerate is
	// choppy or very slow/very fast since millis is independent of framerate.
	if(ofGetElapsedTimeMillis() - redMillis > 500) {
		showRed = !showRed; // toggle drawing the red circle
		
		// reset the timestamp, you must do this otherwise the
		// conditional in the if statement will always be true
		// since the timestamp is never moved up
		redMillis = ofGetElapsedTimeMillis();
	}
	
	// Move the green circle towards the mouse, otherwise wait for 1 second
	// then enable moving.
	if(moveGreen) { // easing calculation to move toward the mouse
		greenX = greenX + (ofGetMouseX() - greenX) * 0.05;
		greenY = greenY + (ofGetMouseY() - greenY) * 0.05;
	}
	else if(ofGetElapsedTimeMillis() - greenMillis > 1000) {
		moveGreen = true; // we can move now!
		greenMillis = ofGetElapsedTimeMillis(); // reset timestamp
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the red circle?
	ofSetColor(220, 120, 120);
	if(showRed) {
		ofDrawCircle(redX, redY, 20);
	}
	ofDrawBitmapString("redMillis: "+ofToString(redMillis), 10, 12);

	// draw the green circle
	ofSetColor(120, 220, 120);
	ofDrawCircle(greenX, greenY, 20);
	ofDrawBitmapString("greenMillis: "+ofToString(greenMillis), 10, 26);
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	// stop the green circle from moving for a little while if the
	// mouse has moved
	moveGreen = false;
	greenMillis = ofGetElapsedTimeMillis(); // reset timestamp
}
