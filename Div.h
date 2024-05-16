#pragma once

#include "UIComponent.h"

enum class PositionLayout {
	LAYOUT_STATIC,
	LAYOUT_FIXED,
	LAYOUT_ABSOLUTE,
	LAYOUT_RELATIVE
};

enum class Display {
	BLOCK,
	INLINE,
	FLEX,
	NONE
};

enum class FlexAlignItem {
	FLEX_START,
	FLEX_END,
	FLEX_CENTER,
	STRETCH,
	SPACE_BETWEEN,
};

enum class FlexJustifyContent {
	FLEX_START,
	FLEX_END,
	FLEX_CENTER,
	SPACE_AROUND,
	SPACE_BETWEEN,
	SPACE_EVENLY
};

class Div : public UIComponent {
// Div properties
private:
	Point _margin;
	Point _padding;

	PositionLayout _positionLayout;
	Display _display;

	Matrix _transform;

public:
	Div() : Div(0, 0, 25, 25) {}
	Div(int x, int y, int w, int h) : 
		UIComponent(x, y, w, h), 
		_margin{0, 0}, 
		_padding{0, 0},
    _positionLayout{PositionLayout::LAYOUT_STATIC},
    _display{Display::BLOCK} {}


	void Render(Graphics& g) override {
		g.TranslateTransform(_margin.X, _margin.Y);
		switch (_positionLayout) {

		}
		g.ResetTransform();
	}

	void RenderChildren(Graphics& g) override { 
		g.TranslateTransform(_padding.X, _padding.Y);


		g.ResetTransform();
	}
};
