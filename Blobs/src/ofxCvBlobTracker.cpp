// ofCvBlobTracker.h by stefanix
// updated by Dan Wilcox <danomatika@gmail.com>
#include "ofxCvBlobTracker.h"

//------------------------------------------------------------------------------
void ofxCvBlobTracker::setListener(ofxCvBlobListener *listener) {
	this->listener = listener;
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::trackBlobs(const vector<ofxCvBlob> &_blobs) {
	unsigned int i, j, k;

	// push to history, clear
	history.push_back(blobs);
	if(history.size() > 4) {
		history.erase(history.begin());
	}
	blobs.clear();

	// load new blobs
	for(i = 0; i < _blobs.size(); i++) {
		blobs.push_back(ofxCvTrackedBlob(_blobs[i]));
	}

	vector<ofxCvTrackedBlob> *prev = &history[history.size()-1];

	int cursize = blobs.size();
	int prevsize = (*prev).size();

	// Now figure out the 'error' (distance) to all blobs in the previous
	// frame. We are optimizing for the least change in distance.
	// While this works really well we could also optimize for lowest
	// deviation from predicted position, change in size etc...
	for(i = 0; i < cursize; i++) {
		blobs[i].error.clear();
		blobs[i].closest.clear();
		for(j = 0; j < prevsize; j++) {
			// calc error - distance to blob in prev frame
			float devX = blobs[i].centroid.x - (*prev)[j].centroid.x;
			float devY = blobs[i].centroid.y - (*prev)[j].centroid.y;
			float error = (float)sqrt(devX*devX + devY*devY);
			blobs[i].error.push_back(error);
			blobs[i].closest.push_back(j);
		}
	}

	// sort so we can make a list of the closest blobs in the previous frame..
	for(i = 0; i < cursize; i++) {
		// bubble sort closest
		for(j = 0; j < prevsize; j++) {
			for(k = 0; k < prevsize-1-j; k++) {
				// ugly as hell, I know
				if(blobs[i].error[blobs[i].closest[k+1]] <
				   blobs[i].error[blobs[i].closest[k]]) {
					int tmp = blobs[i].closest[k]; // swap
					blobs[i].closest[k] = blobs[i].closest[k+1];
					blobs[i].closest[k+1] = tmp;
				}
			}
		}
	}

	// Generate a matrix of all the possible choices.
	// Then we will calculate the errors for every possible match
	// and pick the matrix that has the lowest error.
	// This is an NP complete approach and exponentially increases in complexity
	// with the number of blobs. To remedy for each blob we will only
	// consider the 4 closest blobs of the previous frame.

	// collect id's..
	ids.clear();
	for(i = 0; i < cursize; i++) {
		ids.push_back(-1);
	}

	extraIDs = cursize - prevsize;
	if(extraIDs < 0) {
		extraIDs = 0;
	}
	matrix.clear();

	// FIXME: we could scale numcheck depending on how many blobs there are
	// if we are tracking a lot of blobs, we could check less..
	if(cursize <= 4) {numcheck = 4;}
	else if(cursize <= 6) {numcheck = 3;}
	else if(cursize <= 10) {numcheck = 2;}
	else {numcheck = 1;}
	if(prevsize < numcheck) {
		numcheck = prevsize;
	}
	if(blobs.size() > 0) {
		permute(0);
	}

	unsigned int numResults = matrix.size();

	// loop through all the potential 
	// ID configurations and find one with lowest error
	float bestError = 99999, error;
	int bestErrorNdx = -1;
	for(j = 0; j < numResults; j++) {
		error = 0;
		// get the error for each blob and sum
		for(i = 0; i < cursize; i++) {
			if( matrix[j][i] != -1) {
				error += blobs[i].error[matrix[j][i]];
			}
		}
		if(error < bestError) {
			bestError = error;
			bestErrorNdx = j;
		}
	}

	// now that we know the optimal configuration, 
	// set the IDs and calculate some things..
	if(bestErrorNdx != -1) {
		for(i = 0; i < cursize; i++) {
			if(matrix[bestErrorNdx][i] != -1) {
				blobs[i].id = (*prev)[matrix[bestErrorNdx][i]].id;
			} else {
				blobs[i].id = -1;
			}
			if(blobs[i].id != -1) {
				ofxCvTrackedBlob *oldBlob = &(*prev)[matrix[bestErrorNdx][i]];
				
				blobs[i].deltaLoc.x = (blobs[i].centroid.x - oldBlob->centroid.x);
				blobs[i].deltaLoc.y = (blobs[i].centroid.y - oldBlob->centroid.y);

				blobs[i].deltaArea = blobs[i].area - oldBlob->area;
				
				blobs[i].predictedPos.x = blobs[i].centroid.x + blobs[i].deltaLoc.x;
				blobs[i].predictedPos.y = blobs[i].centroid.y + blobs[i].deltaLoc.y;

				blobs[i].deltaLocTotal.x = oldBlob->deltaLocTotal.x + blobs[i].deltaLoc.x;
				blobs[i].deltaLocTotal.y = oldBlob->deltaLocTotal.y + blobs[i].deltaLoc.y;
			} else {
				blobs[i].deltaLoc = ofPoint( 0.0f, 0.0f );
				blobs[i].deltaArea = 0;
				blobs[i].predictedPos = blobs[i].centroid;
				blobs[i].deltaLocTotal = ofPoint( 0.0f, 0.0f );
			}
		}
	}

	// assign ID's for any blobs that are new this frame (ones that didn't get 
	// matched up with a blob from the previous frame).
	for(i = 0; i < cursize; i++) {
		if(blobs[i].id == -1) {
			blobs[i].id = currentID;
			currentID++;
			if(currentID >= 65535) {
				currentID = 0;
			}
			if(listener) {
				listener->blobEntered(blobs[i].centroid.x,
									  blobs[i].centroid.y,
									  blobs[i].id,
									  findOrder(blobs[i].id));
			}
		}
		else {
			float totalLength = 
				(float)sqrt(blobs[i].deltaLocTotal.x*blobs[i].deltaLocTotal.x +
							blobs[i].deltaLocTotal.y*blobs[i].deltaLocTotal.y);
			if(totalLength >= minimumDisplacementThreshold) {
				if(listener) {
					listener->blobMoved(blobs[i].centroid.x,
										blobs[i].centroid.y,
										blobs[i].id,
										findOrder(blobs[i].id));
				}
				blobs[i].deltaLocTotal = ofPoint(0.0f, 0.0f);
			}
		}
	}

	// if a blob disappeared this frame, send a blob off event
	// for each one in the last frame, see if it still exists in the new frame
	for(i = 0; i < prevsize; i++) {
		bool found = false;
		for(j = 0; j < cursize; j++) {
			if(blobs[j].id == (*prev)[i].id) {
				found = true;
				break;
			}
		}
		if(!found) {
			if(ghostFrames == 0) {
				if(listener) {
					listener->blobExited(blobs[i].centroid.x,
										 blobs[i].centroid.y,
										 blobs[i].id,
										 findOrder(blobs[i].id));
				}
			}
			else if((*prev)[i].markedForDeletion) {
				(*prev)[i].framesLeft -= 1;
				if((*prev)[i].framesLeft <= 0) {
					if(listener) {
						listener->blobExited(blobs[i].centroid.x,
											 blobs[i].centroid.y,
											 blobs[i].id,
											 findOrder(blobs[i].id));
					}
				}
				else {
					// keep it around until framesleft = 0
					blobs.push_back((*prev)[i]);
				}
			}
			else {
				(*prev)[i].markedForDeletion = true;
				(*prev)[i].framesLeft = ghostFrames;
				// keep it around until framesleft = 0
				blobs.push_back((*prev)[i]);
			}
		}
	}
}

//------------------------------------------------------------------------------
int ofxCvBlobTracker::findOrder(int id) const {
	// This is a bit inefficient but ok when
	// assuming low numbers of blobs
	// a better way would be to use a hash table
	int count = 0;
	for(int i = 0; i < blobs.size(); i++) {
		if(blobs[i].id < id) {
			count++;
		}
	}
	return count;
}

//------------------------------------------------------------------------------
ofxCvTrackedBlob& ofxCvBlobTracker::getById(int id) {
	// This is a bit inefficient but ok when
	// assuming low numbers of blobs
	// a better way would be to use a hash table
	for(int i = 0; i < blobs.size(); i++) {
		if(blobs[i].id == id) {
			return blobs[i];
		}
	}
	
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::clear() {
	blobs.clear();
	matrix.clear();
	ids.clear();
	history.clear();
	currentID = 1;
	extraIDs = 0;
	numcheck = 0;
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::draw() {
	draw(0, 0, width, height);
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::draw(float x, float y) {
	draw(x, y, width, height);
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::draw(float x, float y, float w, float h) const {
	
	float scalex = 0.0f;
	float scaley = 0.0f;
	if(width != 0) {scalex = w/width;} else {scalex = 1.0f;}
	if(height != 0) {scaley = h/height;} else {scaley = 1.0f;}
	
	if(bAnchorIsPct) {
		x -= anchor.x * w;
		y -= anchor.y * h;
	}
	else {
		x -= anchor.x;
		y -= anchor.y;
	}

	ofPushStyle();
	// ---------------------------- draw the bounding rectangle
	ofSetHexColor(0xDD00CC);
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(scalex, scaley, 0.0);

	ofNoFill();
	for(int i = 0; i < (int)blobs.size(); i++) {
		ofDrawRectangle(blobs[i].boundingRect.x, blobs[i].boundingRect.y,
						blobs[i].boundingRect.width, blobs[i].boundingRect.height);
	}

	// ---------------------------- draw the blobs
	ofSetHexColor(0x00FFFF);
	ostringstream docstring;
	for(int i = 0; i < (int)blobs.size(); i++) {
		ofNoFill();
		ofBeginShape();
		for(int j = 0; j < blobs[i].nPts; j++) {
			ofVertex(blobs[i].pts[j].x, blobs[i].pts[j].y);
		}
		ofEndShape();

		docstring << findOrder(blobs[i].id) << endl;
		ofDrawBitmapString(docstring.str(), blobs[i].centroid.x, blobs[i].centroid.y);
		docstring.str("");
	}
	glPopMatrix();
	ofPopStyle();
}

//----------------------------------------------------------
void ofxCvBlobTracker::draw(const ofPoint &point) {
	draw(point.x, point.y);
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::draw(const ofRectangle &rect) {
	draw(rect.x, rect.y, rect.width, rect.height);
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::setSize(float w, float h) {
	width = w;
	height = h;
}

//------------------------------------------------------------------------------
float ofxCvBlobTracker::getWidth() const {
	return width;
}

//------------------------------------------------------------------------------
float ofxCvBlobTracker::getHeight() const {
	return height;
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::setAnchorPercent(float xPct, float yPct) {
	anchor.x = xPct;
	anchor.y = yPct;
	bAnchorIsPct = true;
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::setAnchorPoint(int x, int y) {
	anchor.x = x;
	anchor.y = y;
	bAnchorIsPct = false;
}

//------------------------------------------------------------------------------
void ofxCvBlobTracker::resetAnchor() {
	anchor.set(0,0);
	bAnchorIsPct = false;
}

// PROTECTED

//------------------------------------------------------------------------------
inline void ofxCvBlobTracker::permute(int start) {
	if(start == ids.size()) {
		matrix.push_back(ids);
	}
	else {
		int numchecked = 0;
		for(int i = 0; i < blobs[start].closest.size(); i++) {
			if(blobs[start].error[blobs[start].closest[i]] > rejectDistanceThreshold) {
				break;
			}
			ids[start] = blobs[start].closest[i];
			if(checkValid(start)) {
				permute(start+1);
				numchecked++;
			}
			if(numchecked >= numcheck) {
				break;
			}
		}
		if(extraIDs > 0) {
			ids[start] = -1; // new ID
			if(checkValidNew(start)) {
				permute(start+1);
			}
		}
	}
}

//------------------------------------------------------------------------------
inline bool ofxCvBlobTracker::checkValidNew(int start) {
	int newidcount = 1;
	for(int i = 0; i < start; i++) {
		if(ids[i] == -1) {
			newidcount++;
		}
	}
	if(newidcount > extraIDs) {
		return false;
	}
	return true;
}

//------------------------------------------------------------------------------
inline bool ofxCvBlobTracker::checkValid(int start) {
	for(int i = 0; i < start; i++) {
		// check to see whether this ID exists already
		if(ids[i] == ids[start]) {
			return false;
		}
	}
	return true;
}
