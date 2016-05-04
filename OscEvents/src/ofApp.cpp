//
// 2016 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(30);
	ofBackground(100);
	ofSetWindowTitle("OscEvents");
	ofSetCircleResolution(50);
	
	// no cursor please
	ofHideCursor();

	// display font for recieved key values
	font.load(OF_TTF_MONO, 60);

	// listen for OSC messages on port 9001
	receiver.setup(9001);
	
	// send OSC messages to localhost (aka the same computer) on port 9001
	//sender.setup("localhost", 9001);
	
	// send OSC messages to another computer on port 9001
	// replace the IP address below wirth the IP address to the computer
	// you want to send to
	sender.setup("192.168.0.100", 9001);
}

//--------------------------------------------------------------
void ofApp::update(){

	// process any waiting messages in the OSC receiever
	if(receiver.hasWaitingMessages()) {
		
		// our temp message
		ofxOscMessage message;
		
		// load the temp message
		while(receiver.getNextMessage(message)) {
		
			// process the message
			ofLog() << "received OSC to: " << message.getAddress()
			        << " with # args: " << message.getNumArgs();
			
			// mouse events
			if(message.getAddress() == "/mouse/pressed") {
				// check each type before grabbing the data,
				// this is the *safe* way in case you're not sure
				// the type of data you may be getting
				if(message.getArgType(0) == OFXOSC_TYPE_INT32) {
					mousePos.x = message.getArgAsInt(0);
				}
				if(message.getArgType(1) == OFXOSC_TYPE_INT32) {
					mousePos.y = message.getArgAsInt(1);
				}
				buttonDown = true;
				ofLog() << "pressed " << mousePos.x << " " << mousePos.y;
			}
			else if(message.getAddress() == "/mouse/moved") {
				// assume the data types, faster but not as safe
				mousePos.x = message.getArgAsInt(0);
				mousePos.y = message.getArgAsInt(1);
				ofLog() << "moved " << mousePos.x << " " << mousePos.y;
			}
			else if(message.getAddress() == "/mouse/dragged") {
				mousePos.x = message.getArgAsInt(0);
				mousePos.y = message.getArgAsInt(1);
				ofLog() << "dragged " << mousePos.x << " " << mousePos.y;
			}
			else if(message.getAddress() == "/mouse/released") {
				mousePos.x = message.getArgAsInt(0);
				mousePos.y = message.getArgAsInt(1);
				buttonDown = false;
				ofLog() << "released " << mousePos.x << " " << mousePos.y;
			}
			
			// keyboard
			else if(message.getAddress() == "/key/pressed") {
				if(message.getArgType(0) == OFXOSC_TYPE_INT32) {
					key = message.getArgAsInt(0);
				}
				ofLog() << "key pressed " << key;
			}
			else if(message.getAddress() == "/key/released") {
				if(message.getArgType(0) == OFXOSC_TYPE_INT32) {
					key = message.getArgAsInt(0);
				}
				ofLog() << "key released " << key;
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw larger background circle if the mouse button is down
	if(buttonDown) {
		ofSetColor(255);
		ofDrawCircle(mousePos, 100);
	}
	
	// draw the current mouse position
	ofSetColor(200);
	ofDrawCircle(mousePos, 50);
	
	// draw the current key
	ofEnableAlphaBlending();
	ofSetColor(220, 120, 120, 200);
	string s;
	s += (char)key;
	ofRectangle bbox = font.getStringBoundingBox(s, 0, 0);
	font.drawString(s, ofGetWidth()/2 - bbox.width/2, ofGetHeight()/2);
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofxOscMessage message;
	message.setAddress("/key/pressed");
	message.addInt32Arg(key);
	sender.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	ofxOscMessage message;
	message.setAddress("/key/released");
	message.addInt32Arg(key);
	sender.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	ofxOscMessage message;
	message.setAddress("/mouse/moved");
	message.addInt32Arg(x);
	message.addInt32Arg(y);
	sender.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofxOscMessage message;
	message.setAddress("/mouse/dragged");
	message.addInt32Arg(x);
	message.addInt32Arg(y);
	sender.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofxOscMessage message;
	message.setAddress("/mouse/pressed");
	message.addInt32Arg(x);
	message.addInt32Arg(y);
	sender.sendMessage(message);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	ofxOscMessage message;
	message.setAddress("/mouse/released");
	message.addInt32Arg(x);
	message.addInt32Arg(y);
	sender.sendMessage(message);
}
