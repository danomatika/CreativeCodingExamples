#pragma once

#include "State.h"

// the start screen
class GameStart : public State {

	public:

		GameStart() {
			// nothing to create, so this is empty
		}
		
		void setup() {
			ofBackground(255, 0, 0);
		}

		void draw() {
			ofSetColor(0);
			ofDrawBitmapString("start: click to begin", 6, 12);
		}
};
