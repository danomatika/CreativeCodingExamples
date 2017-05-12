#pragma once

#include "State.h"

// game over screen
class GameOver : public State {

	public:
		
		GameOver() {
			// nothing to create, so this is empty
		}
		
		void setup() {
			ofBackground(0, 255, 0);
		}

		void draw() {
			ofSetColor(0);
			ofDrawBitmapString("game over: click to restart", 6, 12);
		}	
};
