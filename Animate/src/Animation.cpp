//
// 2017 Dan Wilcox danomatika.com
// EDP Creative Coding @ the University of Denver
//
#include "Animation.h"

bool Animation::load(const string &directory, const string &extension) {
	clear();
	ofDirectory dir(directory);
	if(!dir.exists()) {
		ofLogError("Animation") << "directory does not exist: " << directory;
		return false;
	}
	if(!dir.isDirectory()) {
		ofLogError("Animation") << "directory is not a directory: " << directory;
		return false;
	}
	if(extension != "") {
		dir.allowExt(extension);
	}
	int numFiles = dir.listDir();
	dir.sort();
	for(int i = 0; i < numFiles; ++i) {
		ofImage image;
		if(image.load(dir.getPath(i))) {
			frames.push_back(image);
		}
	}
	dir.close();
	ofLogNotice("Animation") << "loaded " << frames.size() << " frames from " << directory;
}

void Animation:: clear() {
	frames.clear();
	currentFrame = 0;
}

void Animation::update() {
	if(ofGetElapsedTimeMillis() - timestamp >= frameTime) {
		nextFrame();
		timestamp = ofGetElapsedTimeMillis();
	}
}

void Animation::setFrameTime(int millis) {
	frameTime = millis;
}

void Animation::setFrameRate(float fps) {
	frameTime = 1000 / fps;
}

int Animation::getFrameTime() {
	return frameTime;
}

/// OF BASE DRAWS

void Animation::draw(float x, float y) const {
	draw(x, y, getWidth(), getHeight());
}

void Animation::draw(float x, float y, float w, float h) const {
	if(frames.empty()) {
		return;
	}
	frames[currentFrame].draw(x, y, w, h);
}

float Animation::getWidth() const {
	return frames.empty() ? 0 : frames.front().getWidth();
}

float Animation::getHeight() const {
	return frames.empty() ? 0 : frames.front().getHeight();
}

void Animation::setAnchorPercent(float xPct, float yPct) {
	for(ofImage &frame : frames) {
		frame.setAnchorPercent(xPct, yPct);
	}
}

void Animation::setAnchorPoint(float x, float y) {
	for(ofImage &frame : frames) {
		frame.setAnchorPoint(x, y);
	}
}

void Animation::resetAnchor() {
	for(ofImage &frame : frames) {
		frame.resetAnchor();
	}
}

/// MANUAL FRAME CONTROL

void Animation::nextFrame() {
	currentFrame++;
	if(currentFrame >= frames.size()) {
		currentFrame = 0;
	}
	gotoFrame(currentFrame);
}

void Animation::prevFrame() {
	currentFrame--;
	if(currentFrame < 0) {
		currentFrame = frames.size()-1;
	}
	gotoFrame(currentFrame);
}

void Animation::gotoFrame(int frame) {
	if(frame >= 0 && frame < frames.size()) {
		currentFrame = frame;
	}
	else {
		ofLogWarning("Animation") << "invalid frame: " << frame;
	}
}

int Animation::numFrames() {
	return frames.size();
}
