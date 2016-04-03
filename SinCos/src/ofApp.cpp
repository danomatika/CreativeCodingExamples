//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(ofColor::darkGray);
	ofSetWindowTitle("SinCos");
	ofSetCircleResolution(50);

	// start in the middle
	greenPosY = ofGetHeight()/2;
	greenBaseX = ofGetWidth()/2;
	greenOffsetX = 100;
	greenAngleX = 0;

	// start in the middle
	redBaseX = ofGetWidth()/2;
	redBaseY = ofGetHeight()/2;
	redOffsetX = 150;
	redOffsetY = 150;
	redAngleX = 0;
	redAngleY = 0;
	
	// start at the top off screen
	bluePosX = ofGetWidth()/2;
	blueBaseY = -50;
	blueOffsetY = ofGetHeight()+50;
	blueAngleY = 0;
	blueAngleStep = 0;
	
	// start at the lower right off screen
	yellowPosX = -50;
	yellowBaseY = ofGetHeight();
	yellowOffsetY = ofGetWidth()/2;
	yellowAngleY = 0;
	yellowAngleStep = 0;
	yellowVelX = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	// calc new x position from the base using sin
	greenPosX = greenBaseX + sin(greenAngleX) * greenOffsetX;
	greenAngleX = greenAngleX + 0.025;
	
	// calc new position from the base using sin & cos
	redPosX = redBaseX + sin(redAngleX) * redOffsetX;
	redPosY = redBaseY + cos(redAngleY) * redOffsetY;
	redAngleX = redAngleX + 0.025;
	redAngleY = redAngleY + 0.025;
	
	// stop updating the angle once it gets to PI since
	// we only want to 0-1-0 part of the sin function
	bluePosY = blueBaseY + sin(blueAngleY) * blueOffsetY;
	if(blueAngleY < PI) { // keep updating
		blueAngleY = blueAngleY + blueAngleStep;
	}
	else { // stop updating & reset
		blueAngleY = 0;
		blueAngleStep = 0;
	}
	
	// move horizontally using linear pos + velocity,
	// move vertically using abs(sin) so we only get positive values
	// which we multiple by our offset and *subtract* from the base y position
	// since the Y axis increases towards the bottom in OF
	yellowPosX = yellowPosX + yellowVelX;
	yellowPosY = yellowBaseY - abs(sin(yellowAngleY)) * yellowOffsetY;
	
	// stop updating the angle once we are off the screen to the right
	if(yellowPosX > ofGetWidth()+50) { // stop & reset
		yellowVelX = 0;
		yellowAngleStep = 0;
	}
	else { // keep updating
		yellowAngleY = yellowAngleY + yellowAngleStep;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(120, 220, 120);
	ofDrawCircle(greenPosX, greenPosY, 50);

	ofSetColor(220, 120, 120);
	ofDrawCircle(redPosX, redPosY, 50);

	ofSetColor(120, 120, 220);
	ofDrawCircle(bluePosX, bluePosY, 50);
	
	ofSetColor(220, 220, 120);
	ofDrawCircle(yellowPosX, yellowPosY, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// spacebar
	if(key == ' ') {
	
		// start updating by setting the step to something > 0
		blueAngleStep = 0.025;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// reset pos
	yellowPosX = -50;
	
	// start updating
	yellowVelX = 4;
	yellowAngleStep = 0.075;
}
