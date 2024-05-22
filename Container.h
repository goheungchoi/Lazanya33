#pragma once

#include "UIComponent.h"

using namespace Gdiplus;

enum class Display {
	BLOCK,
	INLINE,
	FLEX,
	NONE
};

enum class FlexDirection {
	ROW,
	COLUMN
};

enum class FlexAlignItem {
	FLEX_START,
	FLEX_END,
	FLEX_CENTER,
	STRETCH,
	SPACE_BETWEEN
};

enum class FlexJustifyContent {
	FLEX_START,
	FLEX_END,
	FLEX_CENTER,
	SPACE_AROUND,
	SPACE_BETWEEN,
	SPACE_EVENLY
};

class Container : public UIComponent {
// Container Display properties
private:
	Display _display;
	FlexDirection _flexDirection{ FlexDirection::ROW };
	FlexAlignItem _flexAlignItem{ FlexAlignItem::FLEX_START };
	FlexJustifyContent _flexJustifyContent{ FlexJustifyContent::FLEX_START };

public:
	Container() : Container(0, 0, 25, 25) {}
	Container(int x, int y, int w, int h) : 
		UIComponent(x, y, w, h), 
    _display{Display::BLOCK} {}

	void SetDisplay(Display display) {
		_display = display;
	}

	void SetFlexDirection(FlexDirection flexDir) {
		_flexDirection = flexDir;
	}

	void SetFlexAlignItem(FlexAlignItem flexAlignItem) {
		_flexAlignItem = flexAlignItem;
	}

	void SetFlexJustifyContent(FlexJustifyContent flexJustifyContent) {
		_flexJustifyContent = flexJustifyContent;
	}

	virtual void Render(Graphics& g) override {
		if (_display == Display::NONE) return;
		
		UIComponent::Render(g);
	}
};
