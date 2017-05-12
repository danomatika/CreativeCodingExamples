#pragma once

#include "ofMain.h"

class Ball {

	public:

		Ball() {
			reset();
		}

		Ball(float x, float y) {
			reset();
			pos.set(x, y);
		}
		
		// reset to random pos & velocity
		void reset() {
			pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
			vel.set(ofRandom(-4, 4), ofRandom(-4, 4));
			awake = true;
			bounces = 0;
		}

		void update() {
		
			// check edges
			if(pos.x < 0 || pos.x > ofGetWidth()) {
			  vel.x = -vel.x;  
			  bounces = bounces+1;
			}
			if(pos.y < 0 || pos.y > ofGetHeight()) {
			  vel.y = -vel.y;
			  bounces = bounces+1;
			}

			// after 4 bounces, this ball is tired and wants to sleep
			if(bounces >= 4) {
			  awake = false;  
			}

			// move
			pos += vel;
		}
	  
		void draw() {
			ofFill();
			ofSetColor(255);
			ofDrawCircle(pos.x, pos.y, 12);
			ofNoFill();
			ofSetColor(0);
			ofDrawCircle(pos.x, pos.y, 12);
		}

		ofPoint pos;
		ofPoint vel;
		
		// number of times the ball has hit the edge of the screen
		int bounces = 0;
	  
		// is this ball awake & active?
		bool awake = true;

};
