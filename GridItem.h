#pragma once

#include "IRenderable.h"

using namespace Gdiplus;

class GridItem : public IRenderable {
protected:
  static std::unordered_map<std::wstring, Bitmap*> _pSpriteRegister;
  static std::unordered_map<std::wstring, CachedBitmap*> _pSpriteCacheData;
	
	// frames where the graphics are drawn actually.
	std::unordered_map<Bitmap*, Rect> _spriteFrames;

	Matrix _gridTransform;
	Point _gridPos;

	// Graphics
	bool _border{false};
  Pen _pen;
  bool _fill{false};
  SolidBrush _brush;

	// Pivot Position
  H_DIRECTION _horizontal{H_DIRECTION::LEFT};
  V_DIRECTION _vertical{V_DIRECTION::TOP};

public:
	std::unordered_map<Bitmap*, Rect> _spriteRects;

	GridItem() {}

	void SetGridPos(int x, int y) {
		_gridPos.X = x;
		_gridPos.Y = y;
	}

	virtual void Render(Graphics& g) {
		Matrix t;
		g.GetTransform(&t);
		g.ResetTransform();





		g.SetTransform(&t);
	}

private:
  /**
   * @brief Adjust a sprite frame based on 
	 *	the Renderable position.
   * @param sprite
   * @param spriteRect
   */
  void __AdjustSpriteRect(Bitmap* sprite, Rect& spriteRect) {
		if (!sprite) return;
		
		unsigned int width = sprite->GetWidth();
    unsigned int height = sprite->GetHeight();
    unsigned int halfW = width / 2;
    unsigned int halfH = height / 2;

    unsigned int frameX = _position.X;
    unsigned int frameY = _position.Y;

    switch (_horizontal) {
      case H_DIRECTION::LEFT: {
      } break;
      case H_DIRECTION::CENTER: {
        frameX -= halfW;
      } break;
      case H_DIRECTION::RIGHT: {
        frameX -= width;
      } break;
    }

    switch (_vertical) {
      case V_DIRECTION::TOP: {
      } break;
      case V_DIRECTION::CENTER: {
        frameY -= halfH;
      } break;
      case V_DIRECTION::BOTTOM: {
        frameY -= height;
      } break;
    }

    spriteRect.X = frameX;
    spriteRect.Y = frameY;
  }
};

template <class T>
std::unordered_map<std::wstring, Bitmap*>
    GridItem<T>::_pSpriteRegister;

template <class T>
std::unordered_map<std::wstring, CachedBitmap*>
    GridItem<T>::_pSpriteCacheData;

#ifndef NDEBUG
inline GridItem<int> GridItemDebugTrigger;
#endif