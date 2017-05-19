// ofCvBlobTracker.h by stefanix
// updated by Dan Wilcox <danomatika@gmail.com>
// Thanks to touchlib for the best fit algorithm!
#pragma once

#include <ofConstants.h>
#include <ofxOpenCv.h>
#include "ofxCvTrackedBlob.h"

/// \class ofxCvBlobListener
/// \brief subclass to recieve blob tracker events
class ofxCvBlobListener {

	public:
	
		/// a blob entered the scene
		virtual void blobEntered(int x, int y, int id, int order) = 0;
	
		/// a blob moved
		virtual void blobMoved(int x, int y, int id, int order) = 0;
	
		/// a bob exited the scene
		virtual void blobExited(int x, int y, int id, int order) = 0;
};

/// \class ofxCvBlobTracker
/// \brief This class tracks blobs between frames.
///
/// Most importantly it assignes persistent id to new blobs, correlates
/// them between frames, and removes them as blobs dissappear. It also
/// compensates for ghost frames in which blobs momentarily dissappear.
///
/// Based on the tracking it fires events when blobs come into existence,
/// move around, and disappear. The object which receives the callbacks
/// can be specified with setListener().
class ofxCvBlobTracker : public ofBaseDraws  {

	public:

		ofxCvBlobTracker() {};

		/// set the listen for blob events, set to nullptr to disable
		void setListener(ofxCvBlobListener *listener);
	
		/// track blobs from contour finder ofxCvBlobs
		///
		/// assign ids to blobs and fire blob events,
		/// this method tracks by proximity and best fit
		void trackBlobs(const vector<ofxCvBlob> &_blobs);
	
		/// find order by which the present blobs came into existence
		int findOrder(int id) const;
	
		/// returns a reference to the corresponding blob in blobs vector
		ofxCvTrackedBlob& getById(int id);
	
		/// clear tracker data
		void clear();

		virtual void draw();
		virtual void draw(float x, float y);
		virtual void draw(float x, float y, float w, float h) const;
		virtual void draw(const ofPoint &point);
		virtual void draw(const ofRectangle &rect);

		/// set draw size to scale blobs into, default: 0x0 draws normal size
		void setSize(float w, float h);
	
		/// get the draw width, default: 0
		float getWidth() const;
	
		/// get the draw height, default: 0
		float getHeight() const;

		/// sey anchor point when drawing via percentage 0-1,
		/// default is upper left corner (0, 0)
		virtual void setAnchorPercent(float xPct, float yPct);
	
		/// set anchor point when drawing, default is upper left corner (0, 0)
		virtual void setAnchorPoint(int x, int y);
	
		/// reset anchor point to upper left corner (0, 0)
		virtual void resetAnchor();
	
		/// tracked blobs
		vector<ofxCvTrackedBlob> blobs;

	protected:

		// helpers
		inline void permute(int k);
		inline bool checkValid(int start);
		inline bool checkValidNew(int start);

		int width = 0;
		int height = 0;
	
		ofxCvBlobListener *listener = nullptr;

		int rejectDistanceThreshold = 150;
		float minimumDisplacementThreshold = 2.0f;
		int ghostFrames = 2;

		int currentID = 1;
		int extraIDs = 0;
		int numcheck = 0;

		vector<vector<int>> matrix;
		vector<int> ids;
		vector<vector<ofxCvTrackedBlob>> history;

		ofPoint anchor;
		bool bAnchorIsPct = false;
};
