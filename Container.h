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

	void RenderChildren(Graphics& g) override { 
		switch (_display) {
		case Display::BLOCK: {
			int childYPos = _y;
			for (UIComponent* pChildComp : _childComponents) {
				if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_FIXED) {
					g.TranslateTransform(_x, _y);
					pChildComp->Render(g);
					g.TranslateTransform(-_x, -_y);
					continue;
				} else if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_ABSOLUTE) {
					pChildComp->Render(g);
					continue;
				}
					
				g.TranslateTransform(_x, childYPos);
				pChildComp->Render(g);
				g.TranslateTransform(-_x, -childYPos);
				childYPos += pChildComp->GetHeight();
			}
		} break;
		case Display::INLINE: {
			int childXPos = _x;
			for (UIComponent* pChildComp : _childComponents) {
				if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_FIXED) {
					g.TranslateTransform(_x, _y);
					pChildComp->Render(g);
					g.TranslateTransform(-_x, -_y);
					continue;
				} else if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_ABSOLUTE) {
					pChildComp->Render(g);
					continue;
				}

				g.TranslateTransform(childXPos, _y);
				pChildComp->Render(g);
				g.TranslateTransform(-childXPos, -_y);
				childXPos += pChildComp->GetWidth();
			}
		} break;
		case Display::FLEX: {
			// Flex direction row ->
			if (_flexDirection == FlexDirection::ROW) {
				int totalWidth = 0;
				for (UIComponent* pChildComp : _childComponents) {
					if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_FIXED) {
						continue;
					} else if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_ABSOLUTE) {
						continue;
					}
					totalWidth += pChildComp->GetWidth();
				}

				// Calculate initial X position based on flex justification
				int startX = _x;
				int remainingSpace = _width - totalWidth;
				int spaceBetween = 0;
				int initialOffset = 0;

				if (_flexJustifyContent == FlexJustifyContent::FLEX_START) {
					startX = _x;
				} else if (_flexJustifyContent == FlexJustifyContent::FLEX_END) {
					startX = _x + remainingSpace;
				} else if (_flexJustifyContent == FlexJustifyContent::FLEX_CENTER) {
					startX = _x + (remainingSpace >> 1);
				} else if (_flexJustifyContent == FlexJustifyContent::SPACE_BETWEEN && 
					_childComponents.size() > 1) {
					spaceBetween = remainingSpace / (_childComponents.size() - 1);
				} else if (_flexJustifyContent == FlexJustifyContent::SPACE_AROUND && 
					!_childComponents.empty()) {
					initialOffset = remainingSpace / (_childComponents.size() << 1);
					startX = _x + initialOffset;
					spaceBetween = initialOffset << 1;
				} else if (_flexJustifyContent == FlexJustifyContent::SPACE_EVENLY && 
					!_childComponents.empty()) {
					spaceBetween = remainingSpace / (_childComponents.size() + 1);
					startX = _x + spaceBetween;
				}

				int currentX = startX;

				for (UIComponent* pChildComp : _childComponents) {
					if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_FIXED) {
						g.TranslateTransform(_x, _y);
						pChildComp->Render(g);
						g.TranslateTransform(-_x, -_y);
						continue;
					}

					// Calculate Y position based on flex alignment
					int childY = _y;
					if (_flexAlignItem == FlexAlignItem::FLEX_START) {
						childY = _y;
					} else if (_flexAlignItem == FlexAlignItem::FLEX_END) {
						childY = _y + _height - pChildComp->GetHeight();
					} else if (_flexAlignItem == FlexAlignItem::FLEX_CENTER) {
						childY = _y + ((_height - pChildComp->GetHeight()) >> 1);
					} else if (_flexAlignItem == FlexAlignItem::STRETCH) {
						// Stretch does not modify Y position but changes height, 
						// not implemented in this snippet
					}

					g.TranslateTransform(currentX, childY);
					pChildComp->Render(g);
					g.TranslateTransform(-currentX, -childY);
        
					currentX += pChildComp->GetWidth() + spaceBetween;
				}
			} 
			// Flex direction column бщ
			else if (_flexDirection == FlexDirection::COLUMN) {
				int totalHeight = 0;
				for (UIComponent* pChildComp : _childComponents) {
					if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_FIXED) {
						continue;
					} else if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_ABSOLUTE) {
						continue;
					}
					totalHeight += pChildComp->GetHeight();
				}

				// Calculate initial X position based on flex justification
				int startY = _y;
				int remainingSpace = _height - totalHeight;
				int spaceBetween = 0;
				int initialOffset = 0;

				if (_flexJustifyContent == FlexJustifyContent::FLEX_START) {
					startY = _y;
				} else if (_flexJustifyContent == FlexJustifyContent::FLEX_END) {
					startY = _y + remainingSpace;
				} else if (_flexJustifyContent == FlexJustifyContent::FLEX_CENTER) {
					startY = _y + (remainingSpace >> 1);
				} else if (_flexJustifyContent == FlexJustifyContent::SPACE_BETWEEN && 
						_childComponents.size() > 1) {
					spaceBetween = remainingSpace / (_childComponents.size() - 1);
				} else if (_flexJustifyContent == FlexJustifyContent::SPACE_AROUND && 
						!_childComponents.empty()) {
					initialOffset = remainingSpace / (_childComponents.size() << 1);
					startY = _y + initialOffset;
					spaceBetween = initialOffset << 1;
				} else if (_flexJustifyContent == FlexJustifyContent::SPACE_EVENLY && 
						!_childComponents.empty()) {
					spaceBetween = remainingSpace / (_childComponents.size() + 1);
					startY = _y + spaceBetween;
				}

				int currentY = startY;

				for (UIComponent* pChildComp : _childComponents) {
					if (pChildComp->GetPositionLayout() == PositionLayout::LAYOUT_FIXED) {
						g.TranslateTransform(_x, _y);
						pChildComp->Render(g);
						g.TranslateTransform(-_x, -_y);
						continue;
					}

					// Calculate Y position based on flex alignment
					int childX = _x;
					if (_flexAlignItem == FlexAlignItem::FLEX_START) {
						childX = _x;
					} else if (_flexAlignItem == FlexAlignItem::FLEX_END) {
						childX = _x + _width - pChildComp->GetWidth();
					} else if (_flexAlignItem == FlexAlignItem::FLEX_CENTER) {
						childX = _x + ((_width - pChildComp->GetWidth()) >> 1);
					} else if (_flexAlignItem == FlexAlignItem::STRETCH) {
						// Stretch does not modify X position but changes height, 
						// not implemented in this snippet
					}

					g.TranslateTransform(childX, currentY);
					pChildComp->Render(g);
					g.TranslateTransform(-childX, -currentY);
        
					currentY += pChildComp->GetHeight() + spaceBetween;
				}
			}
		} break;
		}
	}
};
