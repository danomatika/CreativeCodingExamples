//
// Noise: movement animation using Perlin noise. Perlin noise is a gradient noise
// function which computes random positions and then interpolations between
// those positions. Unlike random, noise returns smoothed values where each is
// a little step either up or down from the previous value. This is useful for
// more realistic semi-random movement.
//
// 2016 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
// See https://en.wikipedia.org/wiki/Perlin_noise for an overview.
//
// Think of noise as a mix of random & the sine function where you give it a
// position (like the angle for sine) and it returns a value from 0 to 1.
//
// ie. to semi-randomly oscillate from 0 to a desired value:
//
//     newValue = ofNoise(noisePos) * desiredValue
//     noisePos = noisePos + step
//
// noisePos is the current position in the 1d noise function.
// step is how much to move the noisePos each frame, smaller values create
// faster movement.
//
// There is a signed version which returns values from -1 to 1 like sin:
//
// ie. to semi-randomly oscillate +/- around a desired value:
//
//    newValue = ofSignedNoise(noisePos) * desiredValue
//    noisePos = noisePos + step
//
// There are also 2d and 3d versions of Perlin noise which are useful for
// creating procedurally generated textures, clouds, & landscapes:
//
//    newValue = ofNoise(x, y) * desiredValue
//    newValue = ofNoise(x, y, z) * desiredValue
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
	
		// blue circles: background circle grid using 2d Perlin noise
		float blueSize; // max size for each grid circle
		float blueNoise; // noise animtion variable
		bool blueAnimate; // animate the circle sizes?

		// green circle: moves horizontally in the window using 1d Perlin noise
		float greenPosX, greenPosY; // position
		float greenBaseX; // base position
		float greenOffsetX; // how much +/- to move the pos
		float greenNoiseX; // noise position animation variable

		// red circle: moves about the window using 1d signed Perlin noise for
		// each axis
		float redPosX, redPosY; // position
		float redBaseX, redBaseY; // base position
		float redNoiseX, redNoiseY; // noise position animation variables
};
