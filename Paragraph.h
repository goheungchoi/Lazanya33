#pragma once

#include "UIComponent.h"

using namespace Gdiplus;

class Paragraph : public UIComponent {

public:
	Paragraph() : UIComponent(0, 0, 1, 1) {}

	Paragraph(int x, int y, int w, int h)
		: UIComponent(x, y, w, h) {}

};
