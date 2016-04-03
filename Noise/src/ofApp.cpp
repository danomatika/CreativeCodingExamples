//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(ofColor::darkGray);
	ofSetWindowTitle("Noise");
	ofSetCircleResolution(50);

	// background grid circle size
	blueSize = 20;

	// start in the middle of the window
	greenPosY = ofGetHeight()/2;
	greenBaseX = ofGetWidth()/2;
	greenOffsetX = ofGetWidth()/2;
	greenNoiseX = 0;

	// start in the middle of the window
	redBaseX = ofGetWidth()/2;
	redBaseY = ofGetHeight()/2;
	redNoiseY = 0.025;
}

//--------------------------------------------------------------
void ofApp::update(){

	// calc new noise position, if animating
	if(blueAnimate) {
		blueNoise = blueNoise + 0.005;
	}

	// calc horz position around a base point
	greenPosX = greenBaseX + ofSignedNoise(greenNoiseX) * greenOffsetX;
	greenNoiseX = greenNoiseX + 0.075;

	// calc position within the window
	redPosX = ofNoise(redNoiseX) * ofGetWidth();
	redPosY = ofNoise(redNoiseY) * ofGetHeight();
	// compare to random noise by uncommenting the following:
	//redPosX = ofRandom(ofGetWidth());
	//redPosY = ofRandom(ofGetHeight());
	redNoiseX = redNoiseX + 0.025; // how much to move each frame
	redNoiseY = redNoiseY + 0.05;
}

//--------------------------------------------------------------
void ofApp::draw(){

	// loop through a 2d background grid and set the circle size using each
	// circle's position in 2d noise
	ofSetColor(120, 120, 220);
	int blueHalfSize = blueSize/2; // save a little cpu by prec-alculating
	for(int bluePosY = blueHalfSize; bluePosY < ofGetHeight(); bluePosY += blueSize) {
		for(int bluePosX = blueHalfSize; bluePosX < ofGetWidth(); bluePosX += blueSize) {
			// calc size from 0 to blueHalfSize with 2d noise,
			// add the growing animation variable to create the animation
			float size = ofNoise(bluePosX+blueNoise, bluePosY+blueNoise) * blueHalfSize;
			ofDrawCircle(bluePosX, bluePosY, size);
		}
	}

	ofSetColor(120, 220, 120);
	ofDrawCircle(greenPosX, greenPosY, 50);

	ofSetColor(220, 120, 120);
	ofDrawCircle(redPosX, redPosY, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	// enable background grid animation with spacebar
	if(key == ' ') {
		blueAnimate = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	// enable background grid animation when spacebar is released
	if(key == ' ') {
		blueAnimate = false;
	}
}
