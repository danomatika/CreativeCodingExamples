//
// Typewriter: type into a string buffer using std::set to keep track of the
// keys being held down. Hint: start typing with the keyboard!
//
// References: http://www.cplusplus.com/reference/set/set
//
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
	
		// current text buffer
		string text;
	
		// font to draw text with
		ofTrueTypeFont font;
	
		// the current keys being held down
		//
		// This is a C++ set which is a container object that only allows
		// values to be entered once. It is optimized for random access (find)
		// as opposed to linear access (looping through indices).
		//
		// In the case of keeping track of keys being held down, we only want
		// a single entry for each key which we can remove once that key is
		// released.
		set<int> keys;
	
		// big font for key held down
		ofTrueTypeFont bigFont;
};
