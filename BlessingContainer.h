#pragma once

#include "Container.h"

using namespace Gdiplus;

enum class BlessingType {
	Anaerobic,
	GoldSeeker,
	Naughty,
	Pummeler,
	SugarGirl,
	TenaciousDwarf,
	Wimp
};

class BlessingContainer : public Container {
	BlessingType _blessingType;

	Bitmap* thumbnail;
	Container title;
	Container explanation;

public:
	BlessingContainer(BlessingType blessingType)
		: _blessingType{ blessingType } {
		AddChildComponent(&title);
		AddChildComponent(&explanation);
	}


	void Draw(Graphics& g) {
		// Set Transform
		g.MultiplyTransform(&_transform);


		// Reset Transform
		Matrix* mClone = _transform.Clone();
		mClone->Invert();
		g.MultiplyTransform(mClone);
	}

};
