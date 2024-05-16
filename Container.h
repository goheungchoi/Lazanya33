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

class Container : public UIComponent {
// Div properties
private:
	Rect _margin;
	Rect _padding;

	PositionLayout _positionLayout;
	Display _display;

	Matrix _innerTransform;

public:
	Container() : Container(0, 0, 25, 25) {}
	Container(int x, int y, int w, int h) : 
		UIComponent(x, y, w, h), 
		_margin{0, 0}, 
		_padding{0, 0},
    _positionLayout{PositionLayout::LAYOUT_STATIC},
    _display{Display::BLOCK} {}

	void SetMargin(int n) {
		_margin = { n, n };
	}

	void SetMargin(int h, int v) {
		_margin = { h, v };
	}

	void SetPadding(int n) {
		_padding = { n, n };
	}

	void SetPadding(int h, int v) {
		_padding = { h, v };
	}

	void Render(Graphics& g) override {
		if (_parentComponent) {
			int __x = _margin.X;
			int __y = _margin.Y;

		}
		switch (_positionLayout) {
			case PositionLayout::LAYOUT_STATIC: {
				// Ignore x, y
			} break;
			case PositionLayout::LAYOUT_FIXED: {
				// Fix the position on the screen
				g.ResetTransform();
			} break; 
			case PositionLayout::LAYOUT_ABSOLUTE: {
				// Use the absolute screen coordinate
			} break;
			case PositionLayout::LAYOUT_RELATIVE: {
				// Relatively placed x, y 
			} break;
		}
	}

	void RenderChildren(Graphics& g) override { 
		g.TranslateTransform(_padding.X, _padding.Y);


		g.ResetTransform();
	}
};
