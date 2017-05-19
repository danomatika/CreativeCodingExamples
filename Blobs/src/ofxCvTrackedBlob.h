// ofCvBlobTracker.h by stefanix
// updated by Dan Wilcox <danomatika@gmail.com>
#pragma once

#include <ofxCvBlob.h>

class ofxCvBlobTracker;

/// \class ofxCvTrackedBlob
/// \brief This class represents a blob with inter-frame information.
/// This includes a persistent id to assume a persistent identity over time.
class ofxCvTrackedBlob : public ofxCvBlob {

	public:

		int id = -1; // persistent id (based on appearance)
	
		ofPoint deltaLoc;
		ofPoint deltaLocTotal;
		ofPoint predictedPos;
		float deltaArea = 0.0f;

		ofxCvTrackedBlob() : ofxCvBlob() {
			area = 0.0f;
			length = 0.0f;
		}

		ofxCvTrackedBlob(const ofxCvBlob& b) {
			area = b.area;
			length = b.length;
			boundingRect = b.boundingRect;
			centroid = b.centroid;
			hole = b.hole;
			pts = b.pts;
			nPts = b.nPts;

			id = -1;        
			deltaArea = 0.0f;
			markedForDeletion = false;
			framesLeft = 0;
		}

		int getLowestError() {
			int best = -1;
			float bestV = 99999.0f;
			for(unsigned int i = 0; i < error.size(); i++) {
				if(error[i] < bestV) {
					best = i;
					bestV = error[i];
				}
			}
			return best;
		}

		// for protected data access
		friend ofxCvBlobTracker;

	protected:

		bool markedForDeletion = false;
		int framesLeft = 0;
		vector<float> error;
		vector<int> closest;  //< sorted ids of the closest points
};
