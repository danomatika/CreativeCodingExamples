//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetWindowTitle("Draw");
	
	// don't clear background every frame
	ofSetBackgroundAuto(false);
	
	// (manually) clear with white background
	ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw a line from previous mouse pos to current mouse pos
	ofSetColor(lineColor);
	ofSetLineWidth(lineWidth);
	if(ofGetMousePressed()) {
		ofDrawLine(ofGetPreviousMouseX(), ofGetPreviousMouseY(),
				   ofGetMouseX(), ofGetMouseY());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	// check pressed key and perform action associated with that key
	if(key == ' ') { // spacebar
		ofBackground(255); // clear the screen with white
	}
	else if(key == '1') {
		lineColor = ofColor(255, 0, 0); // red
	}
	else if(key == '2') {
		lineColor = ofColor(0, 255, 0); // green
	}
	else if(key == '3') {
		lineColor = ofColor(0, 0, 255); // blue
	}
	else if(key == '0') {
		lineColor == ofColor(0); // black
	}
	else if(key == OF_KEY_UP) {
		lineWidth = lineWidth + 1;
		if(lineWidth > 20) {
			lineWidth = 20;
		}
	}
	else if(key == OF_KEY_DOWN) {
		lineWidth = lineWidth - 1;
		if(lineWidth < 1) {
			lineWidth = 1;
		}
	}
	// all other keys are essentially ignored
}
