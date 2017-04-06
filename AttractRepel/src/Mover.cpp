//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "Mover.hpp"

Mover::Mover() {
	pos.x = ofRandom(ofGetWidth());
	pos.y = ofRandom(ofGetHeight());
	vel.x = ofRandom(-4, 4);
	vel.y = ofRandom(-4, 4);
	if(ofRandom(100) > 50) { // 50% change of repelling
		repel = true;
	}
}

void Mover::update(int x, int y) {

	// calculate acceleration based on mouse position and desired behavior
	ofPoint mouse(x, y);
	ofPoint diff;
	if(repel) { // repel from mouse
		diff = pos - mouse;
	}
	else { // attract toward mouse
		diff = mouse - pos;
	}
	diff.normalize(); // normalize to length of 1 as we only want direction
	diff = diff * 0.5; // shorten
	acc = diff;

	// update velocity using acceleration
	vel = vel + acc;
	vel.limit(20); // cap the speed to some certain amount
	
	// udpate position using velocity
	pos = pos + vel;
	
	// wrap around the screen
	if(pos.x <= -radius) { // off left
		pos.x = ofGetWidth()+radius; // go to right
	}
	if(pos.x >= ofGetWidth()+radius) { // off right
		pos.x = -radius; // go to left
	}
	if(pos.y <= -radius) { // off top
		pos.y = ofGetHeight()+radius; // go to bottom
	}
	if(pos.y >= ofGetHeight()+radius) { // off bottom
		pos.y = -radius; // go to top
	}
}

void Mover::draw() {

	// draw the mover
	if(repel) {
		ofSetColor(0, 0, 220); // blue
	}
	else {
		ofSetColor(220, 0, 0); // red
	}
	ofSetLineWidth(1);
	ofDrawCircle(pos, 20);
	
	// draw the direction and speed on top
	ofSetColor(0, 255, 0); // bright green
	ofSetLineWidth(2);
	ofDrawLine(pos.x, pos.y, pos.x+vel.x, pos.y+vel.y);
}

void Mover::toggleBehavior() {
	repel = !repel;
}
