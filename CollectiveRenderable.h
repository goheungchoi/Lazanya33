#pragma once

#include "IRenderable.h"

using namespace Gdiplus;

template <class T>
class MultiSpriteRenderable : public IRenderable {
public:
  static std::unordered_map<std::wstring, Bitmap*> _pSpriteRegister;
  static std::unordered_map<std::wstring, CachedBitmap*> _pSpriteCacheData;

 protected:
  // Cache Data
  bool          _caching;
  Bitmap*       _currentSprite;
  CachedBitmap* _currentCachedBitmap;
  Rect*         _currentSpriteRect;
  std::wstring  _currentTag;

  // Sprite Frames
  std::unordered_map<Bitmap*, Rect> _spriteRects;  // The destination Rect

	// Graphics
	bool _border{false};
  Pen _pen;
  bool _fill{false};
  SolidBrush _brush;

  // Pivot Position
  H_DIRECTION _horizontal{H_DIRECTION::LEFT};
  V_DIRECTION _vertical{V_DIRECTION::TOP};

 public:
  MultiSpriteRenderable(bool caching = true) : 
		// Cache Data
    _caching{caching}, 
    _currentSprite{nullptr}, 
    _currentCachedBitmap{nullptr},
    _currentSpriteRect{nullptr},

		// Graphics
    _pen(Color(0, 0, 0)),
    _brush(Color(0, 0, 0)) {}

  MultiSpriteRenderable(int x, int y, bool caching = true)
  : MultiSpriteRenderable(caching) { SetPosition(x, y); }

	MultiSpriteRenderable(
		int x, 
		int y, 
		H_DIRECTION horizontal, 
		V_DIRECTION vertical, 
		bool caching = true
	) : 
	MultiSpriteRenderable(caching),
  _horizontal{horizontal},
  _vertical{vertical} { SetPosition(x, y); }

	/**
   * @brief 임의의 프레임 포지션과 너비, 높이를 지정하고, 기본 프레임을 생성합니다.
   * @param x 
   * @param y 
   * @param w 
   * @param h 
   * @param caching 
   */
  MultiSpriteRenderable(int x, int y, int w, int h, bool caching = true) 
		: MultiSpriteRenderable(caching) {
		SetPosition(x, y);
		// Create an temporary sprite frame
    _spriteRects[nullptr] = Rect(x, y, w, h);
		_currentSpriteRect = &_spriteRects[nullptr];
	}

  virtual ~MultiSpriteRenderable() {}

	void SetPosition(int x, int y) override { 
		IRenderable::SetPosition(x, y); 
		__AdjustSpriteRect(_currentSprite, *_currentSpriteRect);
	}

  /**
   * @brief ½ºÇÁ¶óÀÌÆ®¸¦ ÅÂ±×¿Í ÇÔ²² ·»´õ·¯ºí ¿ÀºêÁ§Æ®¿¡ ¹ÙÀÎµù ÇÕ´Ï´Ù.
   * @param pSprite ¹ÙÀÎµù ÇÒ ½ºÇÁ¶óÀÌÆ® Æ÷ÀÎÅÍ
   */
  void BindSpriteWithTag(Bitmap* pSprite, const std::wstring& tag) {
		if (!pSprite) {
			throw std::invalid_argument("MultiSpriteRenderable: Sprite is nullptr!");
		}
		
		_pSpriteRegister[tag] = pSprite;

    Rect spriteRect(  // Create the destination rect
      _position.X, 
      _position.Y, 
      pSprite->GetWidth(), 
      pSprite->GetHeight()
    );

    // Adjust the sprite Rect following pivot positions
    __AdjustSpriteRect(pSprite, spriteRect);

    // ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓÀ» ´ã½À´Ï´Ù.
    _spriteRects[pSprite] = std::move(spriteRect);
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
    for (auto& p : _pSpriteRegister) {
      __AdjustSpriteRect(p.second, _spriteRects[p.second]);
    }
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
		_border = true;
		_pen.SetColor(Color(a, r, g, b));
    _pen.SetWidth(width);
	}

	/**
	 * @brief Set fill color of this sprite
	 * @param r Red value from 0~255
	 * @param g Green value from 0~255
	 * @param b Blue value from 0~255
	 * @param a Alpha value from 0~255. Default is 255.
	 */
	void SetFillColor(char r, char g, char b, char a = 255U) {
		_fill = true;
		_brush.SetColor(Color(a, r, g, b));
	}

  /**
   * @brief ÇöÀç ·»´õ¸µ ÇÏ°í ÀÖ´Â ½ºÇÁ¶óÀÌÆ®ÀÇ Æ÷ÀÎÅÍ¸¦ ¸®ÅÏÇÕ´Ï´Ù.
   * @return ½ºÇÁ¶óÀÌÆ®ÀÇ ºñÆ®¸Ê Æ÷ÀÎÅÍ
   */
  Bitmap* GetCurrentSprite() { return _currentSprite; }

  /**
   * @brief ÅÂ±×¿¡ ¸Â´Â ½ºÇÁ¶óÀÌÆ®·Î ÀüÈ¯ÇÕ´Ï´Ù. 
   * ÀÌ ÇÔ¼ö´Â ´Ù¸¥ ÇÔ¼öµé¿¡ ºñ¿¡ »ó´ëÀûÀ¸·Î ´À¸± ¼ö ÀÖ½À´Ï´Ù.
   * @param tag ½ºÇÁ¶óÀÌÆ® ÅÂ±×
   */
  void SetCurrentTag(const wchar_t* tag) {
		if (_caching) {
			// Check if the cached sprite exists
			if (auto cacheIt = _pSpriteCacheData.find(tag); cacheIt == _pSpriteCacheData.end()) 
				_currentCachedBitmap = nullptr;  // If not, mark this sprite has no cache.
			else
				_currentCachedBitmap = cacheIt->second;
		} 
		
		auto it = _pSpriteRegister.find(tag);
		if (it == _pSpriteRegister.end())
      _currentSprite = nullptr;
		else 
			_currentSprite = it->second;

    // Set the current frame
    _currentSpriteRect = &_spriteRects[_currentSprite];
  }

	void CacheData(Graphics& g) override {
		if (_caching) {
			for (auto& it : _pSpriteRegister) {
        _pSpriteCacheData[it.first] = new CachedBitmap(it.second, &g);
			}

			for (auto pChild : _children) {
				pChild->CacheData(g);
			}
		}
	}

  /**
   * @brief
   * @param g
   */
  virtual void Render(Gdiplus::Graphics& g) override {
		Matrix t;
		g.GetTransform(&t);
		g.ResetTransform();

		Point xy{ _currentSpriteRect->X, _currentSpriteRect->Y };
		t.TransformPoints(&xy);

		_caching && 
		_currentCachedBitmap && 
		g.DrawCachedBitmap(
      _currentCachedBitmap, 
      xy.X, xy.Y
    );

		/*if (_caching) {
			if (_currentCachedBitmap) {
				Matrix t;
				g.GetTransform(&t);

				g.ResetTransform();
				if (g.DrawCachedBitmap(
					_currentCachedBitmap,
					_currentSpriteRect->X,
					_currentSpriteRect->Y
				)) {
					throw std::exception("Cache draw failed!");
				}
				g.SetTransform(&t);
			}
		}*/

    // If no caching
    !_caching && 
		_currentSprite && 
		g.DrawImage(_currentSprite, 
			xy.X, xy.Y,
			_currentSpriteRect->Width,
			_currentSpriteRect->Height);

		/*if (_caching) {
			if (_currentCachedBitmap) {
				if (g.DrawImage(
					_currentSprite,
					*_currentSpriteRect
				)) {
					throw std::exception("Sprite draw failed!");
				}
			}
		}*/

		// Draw border if enabled
    _border && 
		g.DrawRectangle(&_pen, 
			xy.X, xy.Y,
			_currentSpriteRect->Width,
			_currentSpriteRect->Height);
		/*g.DrawRectangle(&_pen, _position.X, _position.Y,
		_currentSpriteRect->Width, _currentSpriteRect->Height);*/

		// Fill Rect if enabled
		_fill && 
		g.FillRectangle(&_brush, 
			xy.X, xy.Y,
			_currentSpriteRect->Width,
			_currentSpriteRect->Height);
		/*g.FillRectangle(&_brush, _position.X, _position.Y,
		_currentSpriteRect->Width, _currentSpriteRect->Height);*/
	
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

template <class T>
std::unordered_map<std::wstring, Bitmap*>
    MultiSpriteRenderable<T>::_pSpriteRegister;

template <class T>
std::unordered_map<std::wstring, CachedBitmap*>
    MultiSpriteRenderable<T>::_pSpriteCacheData;

#ifndef NDEBUG
inline MultiSpriteRenderable<int> CollectiveRenderableDebugTrigger;
#endif
