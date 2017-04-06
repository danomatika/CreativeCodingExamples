//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowTitle("AttractRepel");
	ofBackground(ofColor::white);
	
	// fill the vector with 10 Movers
	for(int i = 0; i < 10; i++) {
		Mover *m = new Mover(); // create
		movers.push_back(m); // add to end
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	// update all the movers
	for(int i = 0; i < movers.size(); i++) {
		movers[i]->update(mouseX, mouseY); // pass in current mouse pos
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw all the movers
	for(int i = 0; i < movers.size(); i++) {
		movers[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// toggle mover behavior with spacebar
	if(key == ' ') {
		for(int i = 0; i < movers.size(); i++) {
			movers[i]->toggleBehavior();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// delete moverpointer at front, then remove front
	Mover *begin = movers.front();
	delete begin;
	movers.erase(movers.begin());
	
	// add new mover to back
	Mover *m = new Mover();
	m->pos.x = x;
	m->pos.y = y;
	movers.push_back(m);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
