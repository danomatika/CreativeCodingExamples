#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(30);
	ofBackground(100);

	receiver.setup(9001);
	sender.setup("localhost", 9001);
}

//--------------------------------------------------------------
void ofApp::update(){

	if(receiver.hasWaitingMessages()) {
		ofxOscMessage message;
		if(receiver.getNextMessage(message)) {
		
			ofLog() << "received OSC to: " << message.getAddress() << " with # args: " << message.getNumArgs();
			
			if(message.getAddress() == "/mouse/pressed") {
				int x = 0, y = 0;
				if(message.getArgType(0) == OFXOSC_TYPE_INT32) {
					x = message.getArgAsInt(0);
				}
				if(message.getArgType(1) == OFXOSC_TYPE_INT32) {
					y = message.getArgAsInt(1);
				}
				ofLog() << "/mouse/pressed " << x << " " << y;
			}
			
			else if(message.getAddress() == "/mouse/moved") {
				int x = 0, y = 0;
				x = message.getArgAsInt(0);
				y = message.getArgAsInt(1);
				ofLog() << "/mouse/moved " << x << " " << y;
			}
			
			else if(message.getAddress() == "/key/pressed") {
				char key = ' ';
				if(message.getArgType(0) == OFXOSC_TYPE_INT32) {
					key = message.getArgAsInt(0);
				}
				ofLog() << "/key/pressed " << key;
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

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
