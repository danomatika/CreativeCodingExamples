//
// 2017 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowTitle("DrawOSC");
	ofBackground(255);
	ofSetBackgroundAuto(false);
	
	// set up the OSC receiver using a specfic port num, in this case 777
	receiver.setup(7777);
	
	// set up the OSC sender with the destination IP address and port num,
	// in this case we send to ourself using the 127.0.0.1 localhost address
	//
	// change this IP to another computer running this app to draw on their
	// screen and vice-versa
	//
	// you can also brodcast to *all* machines on the local subnet using
	// the 255 broadcast address:
	//
	// ie. if the network addresses are in the form 192.168.1.*
	//     the broadcast address is 192.168.1.255
	sender.setup("localhost", 7777);
}

//--------------------------------------------------------------
void ofApp::update(){

	// process osc message
	while(receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		
		// print the basic incoming message info?
		if(print) {
			ofLog() << m.getAddress() << " " << m.getRemoteIp();
		}
		
		// processing incoming mouse state message
		// message: /mouse x y button pressed
		if(m.getAddress() == "/mouse") {
			// types: i i i b
			remoteMouseX = m.getArgAsInt(0);
			remoteMouseY = m.getArgAsInt(1);
			remoteMouseButton = m.getArgAsInt(2);
			remoteMousePressed = m.getArgAsBool(3);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableSmoothing();

	// local mouse
	ofSetColor(200, 100, 100);
	if(ofGetMousePressed()) {
		ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 10);
	}
	
	// remote mouse
	ofSetColor(100, 100, 200);
	if(remoteMousePressed) {
		ofDrawCircle(remoteMouseX, remoteMouseY, 10);
	}
	
	ofDisableSmoothing();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// message: /mouse x y button pressed
	ofxOscMessage m;
	m.setAddress("/mouse");
	m.addIntArg(x);
	m.addIntArg(y);
	m.addIntArg(button);
	m.addBoolArg(true); // pressed
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// message: /mouse x y button pressed
	ofxOscMessage m;
	m.setAddress("/mouse");
	m.addIntArg(x);
	m.addIntArg(y);
	m.addIntArg(button);
	m.addBoolArg(true); // pressed
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// message: /mouse x y button pressed
	ofxOscMessage m;
	m.setAddress("/mouse");
	m.addIntArg(x);
	m.addIntArg(y);
	m.addIntArg(button);
	m.addBoolArg(false); // not pressed
	sender.sendMessage(m);
}
