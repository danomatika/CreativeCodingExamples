#pragma once

#include "State.h"
#include "Ball.h"

// the game itself
class Game : public State {

	public:

		void setup() {
		
			// reset the ball for the game
			ball.reset();

			// not done anymore - starting over,
			// this is declared in the base State class
			done = false;
			
			ofBackground(255, 255, 0);
		}
	
		void update() {
			ball.update();
			if(!ball.awake) {
				// game over!
				done = true;
			}
		}

		void draw() {
			
			ofSetColor(0);
			ofDrawBitmapString("zen game: wait for ball to bounce 4 times: "+ofToString(ball.bounces), 6, 12);
			
			ball.update();
			if(ball.awake) {
				ball.draw();
			}
		}
	
		// game variables
		Ball ball;
};
