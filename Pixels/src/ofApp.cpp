//
// 2017 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Pixels");
	ofBackground(255);

	// source image
	image.load("kittens and puppies.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofPixels &pixels = image.getPixels(); // ref to pixels

	if(drawMode == ORIGINAL) {
	
		// draw image normally
		ofSetColor(255);
		image.draw(0, 0, ofGetWidth(), ofGetHeight());
		
		// grab color from pos within image
		color = image.getColor(imageMouseX, imageMouseY);
	}
	else if(drawMode == CORNER) {
	
		// calc scale diff between window image
		float scaleX = ofGetWidth()/image.getWidth();
		float scaleY = ofGetHeight()/image.getHeight();
	
		// simple pixelation using single upper left corner
		for(int y = 0; y < pixels.getHeight(); y = y + stepY) {
			for(int x = 0; x < pixels.getWidth(); x = x + stepX) {
			
				// draw pixelated section
				ofSetColor(pixels.getColor(x, y));
				ofDrawRectangle(x*scaleX, y*scaleY, stepX*scaleX, stepY*scaleY);
			
				// grab color from pos within image
				if((imageMouseX > x  && imageMouseX < x+stepX) &&
				   (imageMouseY > y && imageMouseY < y+stepY)) {
					color = image.getColor(x, y);
				}
			}
		}
	}
	else if(drawMode == AVERAGE) {
	
		int size = stepX * stepY; // subsection size in num pixels
		float r = 0, g = 0, b = 0; // channel sums
		
		// calc scale diff between window image
		float scaleX = ofGetWidth()/image.getWidth();
		float scaleY = ofGetHeight()/image.getHeight();
	
		// average color pixelation
		for(int y = 0; y < pixels.getHeight(); y = y + stepY) {
			for(int x = 0; x < pixels.getWidth(); x = x + stepX) {
			
				// loop through the subsection of the image
				for(int sy = y; sy < y+stepY; sy++) {
					for(int sx = x; sx < x+stepX; sx++) {
						// sum ech color channel
						ofColor c = pixels.getColor(sx, sy);
						r = r + c.r;
						g = g + c.g;
						b = b + c.b;
					}
				}
				// average the channel sums to make the average color
				ofColor avgColor(r/size, g/size, b/size);
				
				// draw the "pixel" section with the computed average color
				ofSetColor(avgColor);
				ofDrawRectangle(x*scaleX, y*scaleY, stepX*scaleX, stepY*scaleY);
				
				// grab color from pos within image
				if((imageMouseX > x  && imageMouseX < x+stepX) &&
				   (imageMouseY > y && imageMouseY < y+stepY)) {
					color = avgColor;
				}
				
				// reset the channel sums
				r = 0;
				g = 0;
				b = 0;
			}
		}
	}

	// draw's circle with color of image under the mouse pos
	ofSetColor(255);
	ofDrawCircle(mouseX, mouseY, 20);
	ofSetColor(color);
	ofDrawCircle(mouseX, mouseY, 15);
	
	// draw the current mode & step size information
	string mode;
	if(drawMode == ORIGINAL) {
		mode = "original";
	}
	else if(drawMode == CORNER) {
		mode = "corner";
	}
	else if(drawMode == AVERAGE) {
		mode = "average";
	}
	ofDrawBitmapStringHighlight("DrawMode (1-3): "+mode, 0, 12);
	ofDrawBitmapStringHighlight("Step (arrows): "+ofToString(stepX)+" "+ofToString(stepY), 0, 32);
	
	// draw the color under the mouse
	ofDrawBitmapStringHighlight("Color: "+ofToString(color), 0, 52);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// draw mode
	if(key == '1') {
		drawMode = ORIGINAL;
	}
	else if(key == '2') {
		drawMode = CORNER;
	}
	else if(key == '3') {
		drawMode = AVERAGE;
	}
	
	// pixelation section width
	else if(key == OF_KEY_LEFT) {
		stepX = stepX - 1;
		if(stepX < 1) {
			stepX = 1;
		}
	}
	else if(key == OF_KEY_RIGHT) {
		stepX = stepX + 1;
		if(stepX > 100) {
			stepX = 100;
		}
	}
	
	// pixelation section height
	else if(key == OF_KEY_UP) {
		stepY = stepY - 1;
		if(stepY < 1) {
			stepY = 1;
		}
	}
	else if(key == OF_KEY_DOWN) {
		stepY = stepY + 1;
		if(stepY > 100) {
			stepY = 100;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	// convert from window pos to pos in image
	x = ofMap(x, 0, ofGetWidth(), 0, image.getWidth());
	y = ofMap(y, 0, ofGetHeight(), 0, image.getHeight());
	
	// keep from grabbing pixels outside the image bounds
	imageMouseX = ofClamp(x, 0, image.getWidth()-1);
	imageMouseY = ofClamp(y, 0, image.getHeight()-1);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
	
	// get file path
	string file = dragInfo.files[0];
	
	// load if it's an allowed file type (checked via extension)
	string ext = ofFilePath::getFileExt(file);
	if(ext == "jpg" || ext == "JPG" || ext == "png" || ext == "PNG") {
		image.load(file);
	}
}
