//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(30);
    ofBackground(100);
	ofSetWindowTitle("Particles");
    ofSetCircleResolution(50);
    
    // Create our circleS.
    for(int i = 0; i < 20; ++i) {
        
        // Create a new circle returns the pointer to this
        // circle in memory and sets it in c.
		//
		// Using the new operator manually creates the circle in memory, so
		// later on, we will need to manually delete the memory when we no
		// longer need it.
        Circle *c = new Circle();
        
        // Push the pointer to the circle onto the vector.
		//
		// What's nice about this, as opposed to the Web example, is that
		// we are not copying the entire Circle object and it's data into the
		// vector, just a pointer to the position in memory for that Circle.
		// Copying small variable types is fine, but quickly becomes unwieldy
		// for larger data.
        circles.push_back(c);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Update each circle in the vector.
	//
	// Here we use a special variable type called an iterator which refers to
	// a specific location with the vector. It's kind of like a regular for loop
	// int i = 0 iterator on steroids that is smart enough to recognize the size
	// of the array as well as handle changes to the array contents. This is
	// important since we want to actually erase things from the vector.
	//
	// Iterators are declared by the C++ container type as well as the type of
	// objects that the container holds. For this case, we need an iterator
	// for the circles vector which holds pointers to Circle classes. The
	// iterator is then declared iter:
	//
	// vector<Circle*>::iterator iter;
	//
	// There are also 2 special iterator positions we can get from the vector:
	// begin() -> returns an iterator referring to the first object &
	// end() -> refers to the end of the vector (*not* the last object). Using
	// these positions, we can loop literally from beginning to end. To go to the
	// next position, we simply increment the iterator line an int ala iter++.
	//
	// Another thing the the iterator can do is be used to access the thing in the
	// vector at the current iterator's position. The iterator is similar to a
	// pointer in that we can deference it to get the thing the iterator refers to.
    vector<Circle*>::iterator iter;
    for(iter = circles.begin(); iter != circles.end();) {
        Circle *c = *(iter); // give me the thing the iterator refers to (dereference)
		
		// Check if the circle has bounced too much.
		if(c->bounces >= maxBounces) {
            
            // Delete the circle from memory, since we don't need it anymore.
			// We have to do this manually since we created the circle in
			// memory manually using the new operator.
			//
			// Now the c pointer doesn't point to anything in memory anymore,
			// the program will crash if you try to use it.
            delete c;
            
            // Remove the circle pointer
            circles.erase(iter);
            // Do not go to the next position, because the next thing is now *here*.
        }
        else {
            // it's still alive, so update it
            c->update();
            iter++; // go to the next position
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Draw all the circles. Grabs the pointer to each circle via it's
	// index in the vector.
//    for(int i = 0; i < circles.size(); ++i) {
//        Circle *c = circles.at(i);
//        c->draw();
//    }
    
    // Draw all the circles. This is the same as the above for loop
	// but handles the index for you and automatically sets the c
	// variable to equal the current circle for each iteration of the
	// loop.
    for(Circle *c : circles) {
        c->draw();
    }
	
	// Display a status message.
    ofSetColor(255);
    ofDrawBitmapString("num circles: "+ofToString(circles.size()), 12, 12);
	ofDrawBitmapString("max bounces: "+ofToString(maxBounces)+ "(-/+)", 12, 24);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// increment or decrement the max number of bounces
	if(key == '=') {
		maxBounces++;
		if(maxBounces > 20) {
			maxBounces = 20;
		}
	}
	else if(key == '-') {
		maxBounces--;
		if(maxBounces < 1) {
			maxBounces = 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// Create a new circle and add it to the vector.
	if(button == OF_MOUSE_BUTTON_LEFT) {
		Circle *c = new Circle();
		c->x = x;
		c->y = y;
		circles.push_back(c);
	}
	else if(button == OF_MOUSE_BUTTON_RIGHT) {
		// "Explode" all the circles from the current mouse position.
		for(Circle *c : circles) {
			c->explodeAt(x, y);
		}
	}
}
