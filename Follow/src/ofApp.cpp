//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetVerticalSync(true);
	ofBackground(ofColor::darkGray);
	ofSetCircleResolution(50);
	
	posX = ofGetWidth()/2;
	posY = ofGetHeight()/2;
	easing = 0.10;
	
	// start with random target
	targetX = ofRandom(ofGetWidth());
	targetY = ofRandom(ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){

	// move towards the mouse
	posX = posX + (targetX - posX) * easing;
	posY = posY + (targetY - posY) * easing;
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// moving circle
	ofSetColor(100, 100, 200); // blue
	ofDrawCircle(posX, posY, 30);
	
	// target
	ofSetColor(220, 220, 120); // yellow
	ofDrawCircle(targetX, targetY, 20);
	
	// draw current positions
	ofSetColor(255);
	string text = "pos: "+ofToString(posX)+" "+ofToString(posY)+"\n"+
	              "target: "+ofToString(targetX)+" "+ofToString(targetY);
	ofDrawBitmapString(text, 10, 10);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// set new target
	targetX = x;
	targetY = y;
}
