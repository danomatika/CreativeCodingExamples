//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// lock framerate to display refresh
	ofSetVerticalSync(true);
	
	// window title
	ofSetWindowTitle("GameState");
	
	// set the current state to the start screen
	state = &start; // convert to pointer using &
	state->setup(); // call setup
}

//--------------------------------------------------------------
void ofApp::update(){

	// update the current state
	state->update();
	
	// check if the game is currently running and is done
	if(state == &game && state->done) {
		// if done, then go to the game over screen
		state = &over;
		state->setup();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the current state
	state->draw();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(state == &start) {
		// start screen
		state = &game; // go to game
		state->setup(); // setup the game
	}
	else if(state == &over) {
		// game over
		state = &start; // go to start screen
		state->setup();
	}
}
