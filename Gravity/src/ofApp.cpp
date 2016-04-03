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
	
	// start in the center with random velocity and acceleration
	pos.x = ofGetWidth()/2;
	pos.y = ofGetHeight()/2;
	vel.x = ofRandom(4, 4);
	vel.y = ofRandom(4);
	acc.x = ofRandom(4);
	acc.y = ofRandom(-4);
	size = 20;
	
	// gravity is downward
	gravity.x = 0;
	gravity.y = 1;
	
	// retain 90% of the vel when bouncing,
	// smaller values will simulate a "heavier" circle
	// while any value >= 1.0 will bounce forever
	damping = 0.9;
}

//--------------------------------------------------------------
void ofApp::update(){

	// only update if not moving the circle when dragging the mouse
	if(!dragging) {
	
		// apply acceleration due to gravity
		vel = vel + gravity;

		// update position using velocity
		pos = pos + vel;
	}
	
	// horz boundary checks
	if(pos.x < size) { // left
		pos.x = size; // stay on the screen
		vel.x = -vel.x; // reverse direction
	}
	else if(pos.x > ofGetWidth()-size) { // right
		pos.x = ofGetWidth()-size;
		vel.x = -vel.x;
	}
	
	// bounce on the bottom slows the velocity a little
	if(pos.y > ofGetHeight() - size) {
		pos.y = ofGetHeight() - size;
		vel.y = -vel.y; // reverse and lose 10% velocity
		vel *= damping;
	}
	else if(pos.y < size) { // top
		pos.y = size;
		vel.y = -vel.y;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(200, 100, 200);
	ofDrawCircle(pos.x, pos.y, size);
	
	// draw the pressed position and connection line when dragging
	if(dragging) {
	
		ofSetColor(120, 220, 120);
		ofDrawCircle(pressed.x, pressed.y, 10);
		
		ofSetColor(220, 220, 120);
		ofDrawLine(pressed.x, pressed.y, ofGetMouseX(), ofGetMouseY());
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
	// set a new circle position
	pos.x = x;
	pos.y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	// start dragging & record pressed position
	dragging = true;
	pressed.x = x;
	pressed.y = y;
	
	// set a new circle position
	pos.x = x;
	pos.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
	// done dragging
	dragging = false;
	
	// calc new velocity using difference from mouse pressed position
	vel.x = x - pressed.x;
	vel.y = y - pressed.y;
	vel.limit(5); // not too fast
	ofLog() << "new vel: " << vel;
}
