#pragma once

#include "IRenderable.h"

using namespace Gdiplus;

template<class T>
class SingleSpriteRenderable : public IRenderable {
public:
	static Bitmap* _pSprite;
  static CachedBitmap* _pSpriteCache;

protected:
	bool _isActive{ true };
	// Cache Data
  bool _caching;
	Rect _spriteRect;	// The destination Rect

  // Graphics
  bool _border{false};
  Pen _pen;
  bool _fill{false};
  SolidBrush _brush;

	// Pivot Position
  H_DIRECTION _horizontal{H_DIRECTION::LEFT};
  V_DIRECTION _vertical{V_DIRECTION::TOP};

public:
	SingleSpriteRenderable(bool caching = true) : 
		_caching{caching},

		// Graphics
    _pen(Color(0, 0, 0)),
    _brush(Color(0, 0, 0)) {}

	SingleSpriteRenderable(int x, int y, bool caching = true) 
		: IRenderable(x, y), SingleSpriteRenderable(caching) {}

  /**
   * @brief 임의의 프레임 포지션과 너비, 높이를 지정합니다.
   * @param x 
   * @param y 
   * @param w 
   * @param h 
   * @param caching 
   */
  SingleSpriteRenderable(int x, int y, int w, int h, bool caching = true) 
		: IRenderable(x, y), SingleSpriteRenderable(caching), _spriteRect(x, y, w, h) {}

	virtual ~SingleSpriteRenderable() {}

	/**
	* @brief ½ºÇÁ¶óÀÌÆ®¸¦ ÀÌ ·»´õ·¯ºí ¿ÀºêÁ§Æ®¿¡ ¹ÙÀÎµùÇÑ´Ù.
	* @param pSprite The pointer to the sprite to be bound
	*/
	void BindSprite(Bitmap* pSprite) { 
		_pSprite = pSprite; 

		INT width, height;
		UIntToInt(pSprite->GetWidth(), &width);
		UIntToInt(pSprite->GetHeight(), &height);
		Rect spriteRect(0, 0, width, height);

		_spriteRect = std::move(spriteRect);
	}

	void BindCachedSprite(CachedBitmap* pCachedSprite) { 
		_pSpriteCache = pCachedSprite; 
	}

	/**
   * @brief ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓÀÇ Æ÷Áö¼ÇÀ» º¯°æµÈ ÇÇ¹þ Æ÷Áö¼Ç¿¡ ¸Â°Ô ¾÷µ¥ÀÌÆ®
   * ÇÕ´Ï´Ù.
   * @param horizontal ¼öÆò ÇÇ¹þ Æ÷Áö¼Ç
   * @param vertical ¼öÁ÷ ÇÇ¹þ Æ÷Áö¼Ç
   */
  void UpdateSpritePivotPosition(H_DIRECTION horizontal, V_DIRECTION vertical) {
    _horizontal = horizontal;
    _vertical = vertical;
    __AdjustSpriteRect(_pSprite, _spriteRect);
  }

	void SetBorderColor(char r, char g, char b, char a = 255U, int width = 1) {
		_border = true;
		_pen.SetColor(Color(a, r, g, b), width);
	}

	void SetFillColor(char r, char g, char b, char a = 255U) {
		_border = true;
		_brush.SetColor(Color(a, r, g, b));
	}

	Bitmap* GetSprite() { return _pSprite; }

	void CacheData(Graphics& g) override {
		if (_caching) {
			_pSpriteCache = new CachedBitmap(_pSprite, &g);

			for (auto pChild : _children) {
				pChild->CacheData(g);
			}
		}
	}

	void SetActive(bool active) {
		_isActive = active;
	}

	virtual void Render(Graphics& g) override {
		if (!_isActive) return;

		Matrix t;
		g.GetTransform(&t);
		g.ResetTransform();

		__AdjustSpriteRect(_pSprite, _spriteRect);

    _caching && 
		_pSpriteCache && 
		g.DrawCachedBitmap(
      _pSpriteCache, 
      _spriteRect.X,
      _spriteRect.Y
    );

		// If no caching
    !_caching && _pSprite && g.DrawImage(_pSprite, _spriteRect);

		// Draw border if enabled
    _border && 
		g.DrawRectangle(&_pen, _spriteRect);

		// Fill Rect if enabled
		_fill && 
		g.FillRectangle(&_brush, _spriteRect);

		RenderChildren(g);

		g.SetTransform(&t);
	}

private:
	/**
   * @brief ÇÇ¹þ Æ÷Áö¼Ç¿¡ ¸Â°Ô ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓÀ» Á¶Á¤ÇÕ´Ï´Ù.
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

template<class T>
Bitmap* SingleSpriteRenderable<T>::_pSprite{ nullptr };

template<class T>
CachedBitmap* SingleSpriteRenderable<T>::_pSpriteCache{ nullptr };

#ifndef NDEBUG
inline SingleSpriteRenderable<int> SingleRenderableDebugTrigger;
#endif
