#pragma once

#include "ofMain.h"

// a base game state class,
// kind of like a mini Sketch
//
// function which can/should be overridden in a subclass
// *must* have the "virtual" keyword before their declaration
class State {

	public:
	
		// set to true when this state is done &
		// we can go to the next state
		bool done = false;

		// setup the state
		virtual void setup() {
			// implement in subclass
		}
	
		// update the state
		virtual void update() {
			// implement in subclass
		}

		// draw the state
		virtual void draw() {
			// implement in subclass
		}	
};
