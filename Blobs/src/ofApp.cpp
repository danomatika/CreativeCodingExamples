//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("Blobs");
	ofBackground(255);
	
	grabber.setup(640, 480);
	
	colorImg.allocate(grabber.getWidth(), grabber.getHeight());
	grayImage.allocate(grabber.getWidth(), grabber.getHeight());
	grayBg.allocate(grabber.getWidth(), grabber.getHeight());
	grayDiff.allocate(grabber.getWidth(), grabber.getHeight());

	threshold = 80;
	learnBackground = true;
	
	// as our ofApp class inherits ofxCvBlobListener, we can give the
	// tracker a pointer to *this* instance so our ofApp blob event
	// functions will be called
	tracker.setListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){

	grabber.update();
	if(grabber.isFrameNew()){
	
		// get color image from grabber and convert to grayscale image
		colorImg.setFromPixels(grabber.getPixels());
		grayImage = colorImg;
		
		// make a copy of the color image if we're learning the background
		if(learnBackground){
			grayBg = grayImage;
			learnBackground = false;
		}

		// difference and threshold the grayscale image to produce a mono image
		// where white pixels denote the overall difference (aka movement)
		// between the grayscale and background image
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// search for blobs within the threshold image
		// arguments: input image, min area, max area, num blobs, holes?
		contourFinder.findContours(grayDiff, 200, (640*480)/3, 3, false);
		
		// feed blobs into blob tracker to assign them ids
		tracker.trackBlobs(contourFinder.blobs);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	tracker.draw();

	ofSetColor(0);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
			  << "press ' ' to capture bg" << endl
			  << "threshold " << threshold << " (press: +/-)" << endl
			  << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			learnBackground = true;
			break;
		case '+':
			threshold ++;
			if(threshold > 255){
				threshold = 255;
			}
			break;
		case '-':
			threshold --;
			if(threshold < 0){
				threshold = 0;
			}
			break;
	}
}

//--------------------------------------------------------------
void ofApp::blobEntered(int x, int y, int id, int order) {
	ofLog() << "blob " << order << " entered at " << x << " " << y;
}

//--------------------------------------------------------------
void ofApp::blobMoved(int x, int y, int id, int order) {
	// blob 0 moves
	if(order == 0) {
		ofLog() << "blob " << order << " " << x << " " << y;
	}
}

//--------------------------------------------------------------
void ofApp::blobExited(int x, int y, int id, int order) {
	ofLog() << "blob " << order << " exited at " << x << " " << y;

}
