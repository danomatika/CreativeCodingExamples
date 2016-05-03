//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//

// Include the class header which contains the declaration for the class.
#include "Circle.h"

Circle::Circle() {
    x = ofRandom(ofGetWidth());
    y = ofRandom(ofGetHeight());
    velX = ofRandom(-4, 4);
    velY = ofRandom(-4, 4);
    size = ofRandom(10, 50);
    color = ofColor(ofRandom(100, 200)); // random grays
}

void Circle::update() {
    
    // linear movement
    x = x + velX;
    y = y + velY;
    
    // keep on the screen (but keep it nice for Jacob)
    if(x < size) {
        velX = -velX;
        x = size;
        bounces++;
    }
    else if(x > ofGetWidth()-size) {
        velX = -velX;
        x = ofGetWidth()-size;
        bounces++;
    }
    if(y < size) {
        velY = -velY;
        y = size;
        bounces++;
    }
    else if (y > ofGetHeight()-size) {
        velY = -velY;
        y = ofGetHeight()-size;
        bounces++;
    }
}

void Circle::draw() {
    
    // draw the circle
    ofFill();
    ofSetColor(color);
    ofDrawCircle(x, y, size);
    
    // draw the number of bounces
    ofSetColor(0);
    ofDrawBitmapString(ofToString(bounces), x, y);
}

void Circle::explodeAt(float newX, float newY) {
    x = newX;
    y = newY;
    velX = ofRandom(-4, 4);
    velY = ofRandom(-4, 4);
}
