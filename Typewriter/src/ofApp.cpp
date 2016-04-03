//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(ofColor::lightGray);

	// load the default system sans-serif font at 20 points
	font.load(OF_TTF_SANS, 20);
	
	// load big font at 120
	bigFont.load(OF_TTF_SANS, 120);
}

//--------------------------------------------------------------
void ofApp::update(){
	// no updaate needed
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the keys held down in the middle of the screen
	if(!keys.empty()) {
		ofSetColor(220, 120, 120, 200);
		
		// build a temp string by appending each char in the set
		// using a for each loop
		string s;
		for(auto c : keys) {
			s = s + (char)c; // convert from int to char
		}
		
		// get the width of the string using the current font,
		// this way we can correctly center the string as it grows and shrinks
		float swidth = bigFont.stringWidth(s);
		bigFont.drawString(s, ofGetWidth()/2-swidth/2, ofGetHeight()/2);
	}
	
	// draw the text buffer using the font
	ofSetColor(ofColor::black);
	font.drawString(text, 20, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// append characters to our text buffer
	if(key == OF_KEY_RETURN) {
		text = text + '\n'; // endline char
	}
	else if(key == OF_KEY_TAB) {
		text = text + "    "; // 4 spaces for a tab char 
	}
	else if(key == OF_KEY_BACKSPACE) {
		if(text.length() > 0) {
			text.pop_back(); // remove last char
		}
	}
	else if(key == OF_KEY_UP) {
		text = text + "UP";
	}
	else if(key == OF_KEY_DOWN) {
		text = text + "DOWN";
	}
	else if(key == OF_KEY_LEFT) {
		text = text + "LEFT";
	}
	else if(key == OF_KEY_RIGHT) {
		text = text + "RIGHT";
	}
	else {
		text = text + (char)key;
		
		// Insert the new key press into the set. Since set only allows the
		// same value once, we don't have to worry if it's already in there
		// or not.
		keys.insert(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	// Remove the key from the set. This is a little more difficult
	// due to the design of the C++ Standard Template Library.
	//
	// We use a special variable type called an iterator which is a generic
	// way to represent a position in a C++ container (vector, map, set, etc).
	//
	// You declare an iterator using the type of container, the type of the
	// value it stores, and "::iterator": container<valuetype>::iterator name;
	//
	// We have to use an iterator since the sets find method returns an
	// iterator for the position of the key in the set or an iterator for the
	// end of the set if nothing is found. This makes sense since a set is not
	// linearly ordered like a vector, so there are not indexes for a set.
	//
	// It's a little funky, but iterators will make more sense as you start to
	// use them more often.
	//
	set<int>::iterator iter = keys.find(key);
	
	// If the iterator refers to the end of the set, the key is not in the set.
	if(iter != keys.end()) {
	
		// Erase the key from the set. The erase method takes an iterator.
		keys.erase(iter);
	}
}
