// AttractRepel: movers are either attracted to or repelled by the mouse
//
// Move the mouse to influence the movers. Click to create a new mover
// (and remove the oldest). Press the spacebar to toggle movers between
// attract and repel behaviors.
//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"
#include "Mover.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		// vector of Mover pointers
		vector<Mover*> movers;
};
