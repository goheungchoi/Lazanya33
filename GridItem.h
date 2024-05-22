#pragma once

#include "IRenderable.h"

using namespace Gdiplus;

class GridItem : public IRenderable {
protected:
	using Tag = std::wstring;

  std::unordered_map<Tag, Bitmap*> _pSpriteRegister;
	// 
  std::unordered_map<Tag, CachedBitmap*> _pSpriteCacheData;
	// Rect that contain the size of the image. X and Y are 0s.
	std::unordered_map<Tag, Rect> _spriteRects;

public:

	/**
	 * @brief Bind the image pointer to this Renderable object.
	 * In order to cache the images, the image pointers must be bound first.
	 * @param bitmap 
	 * @param tag 
	 */
	void BindImage(Bitmap* bitmap, const Tag& tag) {
		if (!bitmap) throw std::invalid_argument("GridItem: bitmap is null!");
		_pSpriteRegister[tag] = bitmap;
		INT width, height;
		UIntToInt(bitmap->GetWidth(), &width);
		UIntToInt(bitmap->GetHeight(), &height);
		_spriteRects[tag] = Rect{0, 0, width, height};
	}

protected:
	// Cache Data
  bool          _caching;
  Bitmap*       _currentSprite;
  CachedBitmap* _currentCachedBitmap;
  Rect*         _currentSpriteRect;
  std::wstring  _currentTag;

	// _position is the actual position on the window screen
	Matrix _gridTransform;	// GridMap will apply its position and scale.
	Point _gridPos;	// Must be 0 ~ gridSize. Set individually.

	// Graphics
	bool _border{false};
  Pen _pen;
  bool _fill{false};
  SolidBrush _brush;

	// Pivot Position
  H_DIRECTION _horizontal{H_DIRECTION::LEFT};
  V_DIRECTION _vertical{V_DIRECTION::TOP};

	// Color Attribute
	ColorMatrix _imageColorMat 
		{1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	ImageAttributes _imageAtt;

public:
	GridItem() : 
		// Cache Data
    _caching{true}, 
    _currentSprite{nullptr}, 
    _currentCachedBitmap{nullptr},
    _currentSpriteRect{nullptr},
		// Graphics
		_pen(Color(0, 0, 0)),
		_brush(Color(0, 0, 0)) {}

	void GridScale(float x, float y) {
		_gridTransform.Scale(x, y);
	}

	void GridTranslate(float x, float y) { 
		_gridTransform.Translate(x, y);
	}

	void SetGridPos(int x, int y) {
		_gridPos.X = x;
		_gridPos.Y = y;
	}

	void ResetGridTransform() {
		_gridTransform.Reset();
	}

// Graphics
	/**
   * @brief Update the sprite pivot point. Default is LEFT, TOP.
   * @param horizontal Horizontal position of the pivot e.i. LEFT, CENTER, RIGHT
   * @param vertical Vertical position of the pivot e.i. TOP, CENTER, BOTTOM
   */
  void SetSpritePivotPosition(H_DIRECTION horizontal, V_DIRECTION vertical) {
    _horizontal = horizontal;
    _vertical = vertical;
  }

	/**
	 * @brief Set border of this sprite.
	 * @param r Red value from 0~255
	 * @param g Green value from 0~255
	 * @param b Blue value from 0~255
	 * @param a Alpha value from 0~255. Default is 255.
	 * @param width Width of the border. Default is 0.01.
	 */
	void SetBorder(char r, char g, char b, char a = 255, float width = 0.01) {
		_pen.SetColor(Color(a, r, g, b));
    _pen.SetWidth(width);
	}
	void EnableBorder(bool enable) { _border = enable; }
	void DisableBorder(bool disable) { _border = disable; }

	/**
	 * @brief Set fill color of this sprite
	 * @param r Red value from 0~255
	 * @param g Green value from 0~255
	 * @param b Blue value from 0~255
	 * @param a Alpha value from 0~255. Default is 255.
	 */
	void SetFillColor(char r, char g, char b, char a = 255U) {
		_brush.SetColor(Color(a, r, g, b));
	}
	void EnableFill(bool enable) { _fill = enable; }
	void DisableFill(bool disable) { _fill = disable; }

	// Color Intensity
	float GetImageIntensity() {
		return _imageColorMat.m[0][0];
	}

	void SetImageIntensity(float ir, float ig, float ib) {
		_imageColorMat.m[0][0] = ir;
		_imageColorMat.m[1][1] = ig;
		_imageColorMat.m[2][2] = ib;
		_imageAtt.SetColorMatrix(
			&_imageColorMat, 
			ColorMatrixFlagsDefault, 
			ColorAdjustTypeBitmap
		);
	}

	void SetCaching(bool cache) {
		_caching = cache;
	}

	void ChangeTag(const wchar_t* tag) {
		if (_caching) {
			// Check if the cached sprite exists
			auto cacheIt = _pSpriteCacheData.find(tag);
			if ( cacheIt == _pSpriteCacheData.end()) 
				_currentCachedBitmap = nullptr; 
			else
				_currentCachedBitmap = cacheIt->second;
		} 
		
		auto it = _pSpriteRegister.find(tag);
		if (it == _pSpriteRegister.end())
      _currentSprite = nullptr;
		else 
			_currentSprite = it->second;

    // Set the current frame
    _currentSpriteRect = &_spriteRects[tag];
  }

// Render
	virtual void Render(Graphics& g) {
		Matrix t;
		g.GetTransform(&t);
		g.ResetTransform();

		// Adjust the sprite frame position
		_position = _gridPos;
		// Transform the cell's upper left corner position on the screen
		_gridTransform.TransformPoints(&_position);
		__SetSpriteRectPosition(_position, _currentSpriteRect);

		_caching && 
		_currentCachedBitmap && 
		g.DrawCachedBitmap(
      _currentCachedBitmap, 
      _currentSpriteRect->X, _currentSpriteRect->Y
    );

		!_caching && 
		_currentSprite && 
		g.DrawImage(
			_currentSprite, 
			*_currentSpriteRect,
			0, 0,
			_currentSprite->GetWidth(),
			_currentSprite->GetHeight(),
			UnitPixel,
			&_imageAtt
		);

		_border && 
		g.DrawRectangle(&_pen, *_currentSpriteRect);

		_fill && 
		g.FillRectangle(&_brush, *_currentSpriteRect);

		g.SetTransform(&t);
	}

// Rendering Utilities

	Bitmap* GetCurrentSprite() { return _currentSprite; }

	/**
	 * @brief Cache the image data bound to this Renderable object.
	 */
	void CacheData(Graphics& g) override {
		if (_caching) {
			for (auto& it : _pSpriteRegister) {
        _pSpriteCacheData[it.first] = new CachedBitmap(it.second, &g);
			}
		}
	}

protected:
  /**
   * @brief Set a sprite Rect position based on 
	 *	the Renderable position.
   * @param sprite
   * @param spriteRect
   */
  void __SetSpriteRectPosition(const Point& cellULCorner, Rect* spriteRect) {

		int width = spriteRect->Width;
    int height = spriteRect->Height;
    int halfW = width >> 1;
    int halfH = height >> 1;

    int frameX = cellULCorner.X;
    int frameY = cellULCorner.Y;

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

    spriteRect->X = frameX;
    spriteRect->Y = frameY;
  }
};
