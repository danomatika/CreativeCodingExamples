//
// Web: a small particle system visualization using a class & vector. Press
// the mouse and/or the spacebar to change the drawing modes.
//
// References:
//  * ofBook: OOPS!: http://openframeworks.cc/ofBook/chapters/OOPs!.html
//  * ofBook: vector: http://openframeworks.cc/ofBook/chapters/stl_vector.html 
//  * http://www.cplusplus.com/reference/vector
//
#pragma once

#include "ofMain.h"

// C++ class definition, the implementation is in the .cpp file
class Circle {
	
	// Everything after the "public" keyword is a public method or variable.
	// there are also "protected" & "private" keywords as well. These keywords
	// are followed by a colon.
	//
	// In a Processing class, everything is public by default. In C++, however,
	// everything is private by default so *always* put "public:" when first
	// writing a new class.
	public:
	
		// A C++ convention is that class methods declarations are written first
		// then followed by class member variables.
	
		// constructor, chooses random size, position, & velocity
		Circle();
	
		// update the circle's position
		void update();
	
		// draw the circle
		void draw();
	
		// how big?
		float size;
	
		// position & velocity
		float x, y;
	
		// velocity
		float velX, velY;
	
		// circle color
		ofColor color;
	
}; // classes *must* end with a semicolon

// our usual ofApp delcaration
class ofApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		// A C++ vector is like a Java ArrayList: it holds a linear array
		// of objects and can dynamically grow or shrink. You must specify the
		// type of object a vector will hold when you declare it, this is done
		// between the < and > characters after the "vector" keyword.
		vector<Circle> circles;
	
		// drawing modes
		bool drawCircles; // draw the circles?
		bool coloredLines; // draw the lines using the circle colors?
};
