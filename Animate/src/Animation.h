//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#pragma once

#include "ofMain.h"

class Animation : public ofBaseDraws {

	public:
	
		/// load frames from a directory,
		/// choose an optional file extension ie. "png", "jpg", etc
		///
		/// assumes all images are the same size and named sequentially
		bool load(const string &directory, const string &extension="");
	
		/// clear currently loaded frames
		void clear();
	
		/// update the current frame based on the frame time
		///
		/// if you want to manually control the current frame via nextFrame()
		/// & prevFrame() then simply do not call this
		void update();
	
		/// set the number of milliseconds between frames
		void setFrameTime(int millis);
	
		/// set the number of frames per second (converted to milliseconds)
		void setFrameRate(float fps);
	
		/// get the number of milliseconds between frames
		int getFrameTime();
	
		/// \section ofBaseDraws functionality
	
		void draw(float x, float y) const;
		void draw(float x, float y, float w, float h) const;
	
		float getHeight() const;
		float getWidth() const;

		void setAnchorPercent(float xPct, float yPct);
		void setAnchorPoint(float x, float y);
		void resetAnchor();
	
		/// \section Manual Frame Control
	
		/// go to the next frame
		void nextFrame();
	
		/// go to the previous frame
		void prevFrame();
	
		/// go to a specific frame via it's index
		void gotoFrame(int frame);
	
		/// get the number of frames
		int numFrames();
	
	protected:
	
		vector<ofImage> frames;
		int currentFrame = 0;
		long timestamp = 0;
		int frameTime = 40;
};
