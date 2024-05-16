#pragma once

#include "UIComponent.h"

enum class PositionLayout {
	LAYOUT_STATIC,
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
	PositionLayout _positionLayout;
	Display _display;
	FlexAlignItem _flexAlignItem;
	FlexJustifyContent _flexJustifyContent;

	Matrix _innerTransform;

public:
	Container() : Container(0, 0, 25, 25) {}
	Container(int x, int y, int w, int h) : 
		UIComponent(x, y, w, h), 
    _positionLayout{PositionLayout::LAYOUT_STATIC},
    _display{Display::BLOCK} {}

	void Render(Graphics& g) override {
		if (_display == Display::NONE) return;

		switch (_positionLayout) {
			case PositionLayout::LAYOUT_STATIC: {
				// Ignore position of itself, 
				// but follow the layout of the parent
				// Draw image if exists
				_pImage && 
				g.DrawImage(_pImage, _x, _y, _width, _height);

				// TODO: When drawing borders,
				// Don't apply scaling
				// Draw border if enabled

				_border && 
				//g.DrawRectangle(&_pen, *_currentSpriteRect);
				g.DrawRectangle(&_pen, _x, _y, _width, _height);

				// Fill Rect if enabled
				_fill && 
				//g.FillRectangle(&_brush, *_currentSpriteRect);
				g.FillRectangle(&_brush, _x, _y, _width, _height);

				// Draw Text
				!_text.empty() && 
				g.DrawString(_text.c_str(), -1, _pFont, _textPosition, &_textFormat, &_textBrush);
  
				RenderChildren(g);

			} break;
			case PositionLayout::LAYOUT_ABSOLUTE: {
				// Use the absolute screen coordinate
				// Reset the global transformation
				Matrix tmp;
				g.GetTransform(&tmp);
				g.ResetTransform();

				// Draw
				UIComponent::Render(g);

				// Restore the global transformation
				g.SetTransform(&tmp);

			} break;
			case PositionLayout::LAYOUT_RELATIVE: {
				// Relatively placed x, y 
				UIComponent::Render(g);
			} break;
		}
	}

	void RenderChildren(Graphics& g) override { 
		switch (_display) {
		case Display::BLOCK: {
			int _childYPos = _y;
			for (UIComponent* pChildComp : _childComponents) {
				pChildComp->SetPosition(_x, _childYPos);
				pChildComp->Render(g);
				_childYPos += pChildComp->GetY();
			}
		} break;
		case Display::INLINE: {
			int _childXPos = _x;
			for (UIComponent* pChildComp : _childComponents) {
				pChildComp->SetPosition(_childXPos, _y);
				pChildComp->Render(g);
				_childXPos += pChildComp->GetX();
			}
		} break;
		case Display::FLEX: {

		} break;
		}
	}
};
