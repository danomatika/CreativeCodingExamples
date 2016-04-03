//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(ofColor::lightGray);
	ofSetCircleResolution(50);

	targetX = ofGetWidth()-20;

	// red circle
	redX = 20;
	redY = ofGetHeight()*0.25;
	redEasing = 0.02; // 2%
	
	// green circle
	greenX = 20;
	greenY = ofGetHeight()*0.5;
	greenEasing = 0.05; // 5%
	
	// blue circle
	blueX = 20;
	blueY = ofGetHeight()*0.75;
	blueEasing = 0.10; // 10%
}

//--------------------------------------------------------------
void ofApp::update(){

	// move each circle toward the target by a certain amount each frame
	redX = redX + (targetX - redX) * redEasing;
	greenX = greenX + (targetX - greenX) * greenEasing;
	blueX = blueX + (targetX - blueX) * blueEasing;
}

//--------------------------------------------------------------
void ofApp::draw(){

	// red circle
	ofSetColor(200, 100, 100);
	ofDrawCircle(redX, redY, 20);
	ofDrawBitmapString(ofToString(redEasing*100)+"% easing", 10, redY);
	
	// green circle
	ofSetColor(100, 200, 100);
	ofDrawCircle(greenX, greenY, 20);
	ofDrawBitmapString(ofToString(greenEasing*100)+"% easing", 10, greenY);
	
	// blue circle
	ofSetColor(100, 100, 200);
	ofDrawCircle(blueX, blueY, 20);
	ofDrawBitmapString(ofToString(blueEasing*100)+"% easing", 10, blueY);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// reset positions
	redX = 0;
	greenX = 0;
	blueX = 0;
}
