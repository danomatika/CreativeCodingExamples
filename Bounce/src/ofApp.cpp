//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// lock framerate to display refresh
	ofSetVerticalSync(true);
	
	// smoother circles
	ofSetCircleResolution(50);
	
	// set background color
	ofBackground(ofColor::lightGray);

	// init starting pos
	posX = ofGetWidth()/2;
	posY = ofGetHeight()/2;

	// init starting vel
	velX = -3;
	velY = -6;
	
	size = 25;
	isCircle = true;
}

//--------------------------------------------------------------
void ofApp::update(){

	// update movement
	posX = posX + velX;
	posY = posY + velY;
	
	// check if going off the screen, reverse direction if so
	if(posX < size || posX > ofGetWidth()-size) {
		velX = -velX;
	}
	if(posY < size || posY > ofGetHeight()-size) {
		velY = -velY;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// draw circle or rectangle
	ofSetColor(200, 100, 100);
	if(isCircle) {
		ofDrawCircle(posX, posY, size);
	}
	else {
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofDrawRectangle(posX, posY, size*2, size*2);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	posX = x;
	posY = y;
	velX = ofRandom(-6, 6);
	velY = ofRandom(-6, 6);
}
