// Mover: a simple circle mover with behavior based on a given position
//
// red: attracted to the update position
// blue: repelled by the update position
//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

class Mover {

	public:

		Mover(); // constructor
	
		// setup with random postion & velocity
		void setup();
	
		// pass in the mouse position
		void update(int x, int y);
	
		// draw the mover
		void draw();
	
		// toggle between repelling and attracting
		void toggleBehavior();
	
		ofPoint pos; // where we currently are
		ofPoint vel; // direction & speed of where we are heading
		ofPoint acc; // acceleration based on mouse position
	
		bool repel = false; // run away? (default: attract)
		float radius = 20;  // radis of the mover aka size/2
};
