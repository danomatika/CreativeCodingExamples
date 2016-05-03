//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#pragma once

// We want to work with OF, so include the header
// so these files know about the OF API.
#include "ofMain.h"

// A simple circle particle that bounces around the screen. It displays the
// number of bounces using a bitmap string.
class Circle {

	// Make sure to start with public: so that C++ knows the following variables
	// and functions should be accesible when working with instances of Circle.
	public:
		
		// Constructor. Creates a new circle with random initial values.
		Circle();
		
		// Update the position.
		void update();
		
		// Draw to the screen.
		void draw();
		
		// Gravitate towards this position & choose a new velocity.
		void explodeAt(float newX, float newY);
		
		// Circle data
		float x, y;
		float velX, velY;
		float size;
		ofColor color;
		
		// How many times the circle has bounced off the screen.
		int bounces = 0;
};
