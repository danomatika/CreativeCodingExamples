//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(ofColor::darkGray);
	ofSetWindowTitle("Web");
	ofSetCircleResolution(50);

	// make some circles
	for(int i = 0; i < 100; ++i) {
		
		// This creates a new circle by calling the
		// Circle() constructor implicitly.
		Circle circle;
		
		// Add the new Circle to the end of the vector.
		//
		// C++ actually makes a copy of the object in order to do this, which
		// is fine for primitive variables (int, float, etc) and small classes
		// like Circle but is slow and wasteful for larger objects. The best
		// approach is to use a pointer which requires a little more care and
		// is covered in another example.
		circles.push_back(circle);
	}
	
	drawCircles = false; // no circles
	coloredLines = false; // grayscale lines
}

//--------------------------------------------------------------
void ofApp::update(){

	// Update the position of all the circles.
	//
	// This is a for each loop in C++. The "auto" keyword to implicitly
	// chooses the type based on what objects the circles vector holds. It
	// then runs through the vector one object at a time and the circle variable
	// will refer to the object at each index in the vector for each call of the
	// loop. Basically, the following is equivalent to:
	//
	// for(int i = 0; i < circles.size(); ++i) {
	//   Circle circle = circles[i];
	//   circle.draw();
	// }
	//
	// This is much simpler to write and use when you don't need the index.
	//
	for(auto &circle : circles) {
	
		// update position
		circle.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Draw all the circles.
	//
	// Using is a standard for loop since we need to use the index and the
	// previous index.
	for(int i = 0; i < circles.size(); ++i) {
	
		// 1 way to get an object from a vector by index,
		// use a reference since we don't want a copy
		Circle &circle = circles.at(i);
		if(drawCircles) {
			circle.draw();
		}
		
		// draw lines connecting each circle to the previous circle
		if(i > 0) { // ignore the first circle since there is no index -1
			
			// the more standard way to get an object from a vector is is to use
			// the array index operator aka []
			Circle &prevCircle = circles[i-1];
			
			// calc the positive difference between the circles sizes
			float sizeDiff = abs(circle.size - prevCircle.size);
			
			// choose darker lines for a larger difference,
			// the max difference is max size - min size so : 40-10 = 30
			if(coloredLines) {
				ofColor interpolatedColor = ofColor(circle.color);
				interpolatedColor.setBrightness(ofMap(sizeDiff, 0, 30, 255, 55));
				ofSetColor(interpolatedColor);
			}
			else { // grayscale
				ofSetColor(ofMap(sizeDiff, 0, 30, 255, 55));
			}
			
			// draw line
			ofDrawLine(prevCircle.x, prevCircle.y, circle.x, circle.y);
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == ' ') {
		drawCircles = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == ' ') {
		drawCircles = false;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	coloredLines = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	coloredLines = false;
}

//--------------------------------------------------------------
// Circle class implementation
//
// Class methods include the name of the class appended to the method name via
// two colons "::" in the implementation file. This way you can mix methods with
// the same name but between different classes in the same file.

//--------------------------------------------------------------
// constructor, no return type like Java
Circle::Circle() {

	size = (ofRandom(10, 40));
	
	x = ofRandom(size, ofGetWidth()-size);
	y = ofRandom(size, ofGetHeight()-size);
	
	// choose a random velocity based on the size of the circle,
	// larger circles are slower and smaller circles are faster
	float speed = ofMap(size, 10, 40, 6, 1);
	velX = ofRandom(-speed, speed);
	velY = ofRandom(-speed, speed);
	
	// random color please
	color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

//--------------------------------------------------------------
void Circle::update() {
	
	// screen boundary check
	if(x < size || x > ofGetWidth()-size) {
		velX = -velX;
	}
	if(y < size || y > ofGetHeight()-size) {
		velY = -velY;
	}
	
	// move
	x = x + velX;
	y = y + velY;
}

//--------------------------------------------------------------
void Circle::draw() {
	ofSetColor(color);
	ofDrawCircle(x, y, size);
}
