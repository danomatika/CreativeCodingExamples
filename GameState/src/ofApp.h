//
// GameState: game state control using classes and a current state pointer
//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

#include "GameStart.h"
#include "Game.h"
#include "GameOver.h"

class ofApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
	
		GameStart start; // start screen instance
		Game game; // game instance
		GameOver over; // game over screen instance

		// the current state
		// this is a pointer to either start, game, or over
		State *state = nullptr;	
};
