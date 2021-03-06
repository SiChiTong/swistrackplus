#ifndef HEADER_ComponentMotionTemplateTracking
#define HEADER_ComponentMotionTemplateTracking

#include <cv.h>
//#include <cvaux.hpp>
extern "C" {
#include "camshift_wrapper.h"
}
#include "Component.h"
#include "DataStructureParticles.h"

//! A basic tracking component that takes pre-filtered particales and
// adds them to the nearest track.
class ComponentMotionTemplateTracking: public Component {

public:
	//! Constructor.
	ComponentMotionTemplateTracking(SwisTrackCore *stc);
	//! Destructor.
	~ComponentMotionTemplateTracking();

	// Overwritten Component methods
	void OnStart();
	void OnReloadConfiguration();
	void OnStep();
	void OnStepCleanup();
	void OnStop();
	Component *Create() {
		return new ComponentMotionTemplateTracking(mCore);
	}

private:
	DataStructureParticles::tParticleVector mParticles;



	void update_mhi( IplImage* img, IplImage* dst, IplImage * foregroundMask, double timestampIn,
			 int diff_threshold, wxDateTime frameTimestamp );



	IplImage * mOutputImage;

	// motion template variables

	// various tracking parameters (in seconds)
	double mMhiDuration;
	double mSegmentThreshold;
	int mDiffThreshold;
	double mMaxTimeDelta;
	double mMinTimeDelta;
	// number of cyclic frame buffer used for motion detection
	// (should, probably, depend on FPS)
	const int N;

	// ring image buffer
	IplImage **buf;
	int last;
	IplImage *mhi; // MHI
	IplImage *orient; // orientation
	IplImage *mask; // valid orientation mask
	IplImage *segmask; // motion segmentation map
	CvMemStorage* storage; // temporary storage
	double firstTimestamp;

	IplImage *mForegroundMask; // MHI

	IplImage * mInputChannels[3];

	Display mDisplayOutput;									//!< The Display showing the last acquired image and the particles.
};

#endif

