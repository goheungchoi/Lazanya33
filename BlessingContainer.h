#pragma once

#include "Container.h"

using namespace Gdiplus;

enum class BlesssingType {

};

class BlessingContainer : public Container {
	Bitmap* thumbnail;
	Container title;
	Container explanation;

public:
	BlessingContainer() {
		AddChildComponent(&title);
		Add
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
