#pragma once

#include "ofxCv.h"
using namespace ofxCv;

template<typename Tracker>
class ofxFaceTrackerMulti
{
public:
	void setup(int maximum=1);
	bool update(cv::Mat image);
	vector<Tracker*>& getTrackers() { return trackers_; }
	int getDiscardSize() { return discard_size_; }
private:
	vector<Tracker*> trackers_;
	int discard_size_;
};

template<typename Tracker>
void ofxFaceTrackerMulti<Tracker>::setup(int maximum)
{
	trackers_.resize(maximum);
	for(int i = 0; i < maximum; ++i) {
		trackers_[i] = new Tracker();
		trackers_[i]->setup();
	}
	discard_size_ = 25;
}
template<typename Tracker>
bool ofxFaceTrackerMulti<Tracker>::update(cv::Mat image)
{
	for(Tracker *tracker : trackers_) {
		if(tracker->update(image)) {
			cv::circle(image, toCv(tracker->getPosition()), tracker->getScale()*discard_size_, cv::Scalar(0,0,0), -1);
		}
		else {
			image.setTo(cv::Scalar(0,0,0));
		}
	}
}

