//
// Pixels: draw an image manually using it's pixel data
//
// 2017 Dan Wilcox
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

// controls:
//   * change draw mode: 1-3
//   * arrow keys: change pixelation section size width / height
//
// drag an image onto the window to load it
//
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
	
		void dragEvent(ofDragInfo dragInfo);
	
		ofImage image; // image to read pixels from
	
		ofColor color; // current color in the image under the mouse
		int imageMouseX = 0; // mouse x pos within the image
		int imageMouseY = 0; // mosue y pos within the image
	
		// enumeration: creates a custom type that gives names to integers,
		// this is useful for state or mode as it makes the setting more
		// obvious ie. ORIGINAL instead of 0
		enum DrawMode {
			ORIGINAL, // draw image normally
			CORNER,   // pixelate image using single pixel color per section
			AVERAGE   // pixelate image using average section color
		};
		DrawMode drawMode = ORIGINAL; // current mode
	
		int stepX = 30; // pixelated section width in image pixels
		int stepY = 30; // pixelated section height in image pixels
};
