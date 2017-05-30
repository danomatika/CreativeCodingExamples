//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Animate");
	
	// a blue background
	ofBackground(4, 53, 101);
	
	// loads all ".png" frames from the bin/data/nyan directory
	nyan.load("nyan", "png");
}

//--------------------------------------------------------------
void ofApp::update(){

	// update the frame based on the animation frame time,
	// you can also advance frames manually using nextFrame() & prevFrame()
	nyan.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the current frame,
	// this works like ofImage ala draw(x, y), draw(x, y, w, h), etc
	nyan.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	nyan.setFrameRate(ofMap(x, 0, ofGetWidth(), 5, 60));
}
