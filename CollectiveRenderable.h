#pragma once

#include "IRenderable.h"

using namespace Gdiplus;

template <class T>
class CollectiveRenderable : public IRenderable {
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

  // Text Data
  std::wstring    _text;
  PointF          _textPosition;
  FontFamily*     _pFontFamily;
  Font*           _pFont;
  StringFormat    _textFormat;  // Text alignment
  SolidBrush      _textBrush;  // Color of the text

 public:
  CollectiveRenderable(bool caching = true) : 
		// Cache Data
    _caching{caching}, 
    _currentSprite{nullptr}, 
    _currentCachedBitmap{nullptr},
    _currentSpriteRect{nullptr},

		// Graphics
    _pen(Color(0, 0, 0)),
    _brush(Color(0, 0, 0)),

		// Text Data
    _textPosition(0.0f, 0.0f),
    _pFontFamily(new FontFamily(L"Arial")), 
    _pFont(new Font(_pFontFamily, 12, FontStyleRegular, UnitPixel)),
    _textBrush(Color(255, 0, 0, 0)) {}

  CollectiveRenderable(int x, int y, bool caching = true)
  : CollectiveRenderable(caching) { SetPosition(x, y); }

	CollectiveRenderable(
		int x, 
		int y, 
		H_DIRECTION horizontal, 
		V_DIRECTION vertical, 
		bool caching = true
	) : 
	CollectiveRenderable(caching),
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
  CollectiveRenderable(int x, int y, int w, int h, bool caching = true) 
		: CollectiveRenderable(caching) {
		SetPosition(x, y);
    _spriteRects[nullptr] = Rect(x, y, w, h);
		_currentSpriteRect = &_spriteRects[nullptr];
	}

  virtual ~CollectiveRenderable() {}

	/*void SetPosition(int x, int y) override { 
		IRenderable::SetPosition(x, y); 
	}*/

  /**
   * @brief ½ºÇÁ¶óÀÌÆ®¸¦ ÅÂ±×¿Í ÇÔ²² ·»´õ·¯ºí ¿ÀºêÁ§Æ®¿¡ ¹ÙÀÎµù ÇÕ´Ï´Ù.
   * @param pSprite ¹ÙÀÎµù ÇÒ ½ºÇÁ¶óÀÌÆ® Æ÷ÀÎÅÍ
   */
  void BindSpriteWithTag(Bitmap* pSprite, const std::wstring& tag) {
		if (!pSprite) {
			throw std::invalid_argument("CollectiveRenderable: Sprite is nullptr!");
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
   * @brief ÀÌ ¿ÀºêÁ§Æ®°¡ Ç¥½ÃÇÒ ÅØ½ºÆ®¸¦ ¼³Á¤ÇÑ´Ù.
   */
  void SetText(const wchar_t* text) { _text.assign(text); }
  void SetTextPosition(float x, float y) { _textPosition = {x, y}; }

  /**
   * @brief ÅØ½ºÆ®ÀÇ ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓ ¾È¿¡¼­ÀÇ »ó´ëÀû À§Ä¡¸¦ ¸®ÅÏÇÑ´Ù.
   * @return »ó´ëÀû À§Ä¡ÀÇ X°ª
   */
  float GetTextPositionX() { return _textPosition.X; }
  /**
   * @brief ÅØ½ºÆ®ÀÇ ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓ ¾È¿¡¼­ÀÇ »ó´ëÀû À§Ä¡¸¦ ¸®ÅÏÇÑ´Ù.
   * @return »ó´ëÀû À§Ä¡ÀÇ Y°ª
   */
  float GetTextPositionY() { return _textPosition.Y; }
  /**
   * @brief ÅØ½ºÆ®ÀÇ ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓ ¾È¿¡¼­ÀÇ »ó´ëÀû À§Ä¡¸¦ ¸®ÅÏÇÑ´Ù.
   * @return PointF ½ºÆ®·°ÃÄ
   */
  PointF GetTextPosition() { return _textPosition; }

  /**
   * @brief ÆùÆ® ÆÐ¹Ð¸®¸¦ ¼³Á¤ÇÕ´Ï´Ù.
   * @param fontFamily ÆùÆ® ÆÐ¹Ð¸®, ¿¹½Ã) L"Arial"
   */
  void SetFontFamily(const wchar_t* fontFamily) {
    _pFontFamily = new FontFamily(fontFamily);
  }

  /**
   * @brief ÅØ½ºÆ®ÀÇ ÆùÆ®¸¦ ¼³Á¤ÇÑ´Ù.
   * @param fontSize ÇÈ¼¿ ´ÜÀ§ ÆùÆ® »çÀÌÁî
   * @param fontStyle ÆùÆ® ½ºÅ¸ÀÏ, ±âº»°ª = Regular
   * @param unit ÆùÆ® ´ÜÀ§, ±âº»°ª = Pixel
   */
  void SetFont(int fontSize, FontStyle fontStyle = FontStyleRegular,
               Unit unit = UnitPixel) {
    _pFont = new Font(_pFontFamily, fontSize, fontStyle, unit);
  }

  /**
   * @brief ÅØ½ºÆ®ÀÇ »ö±òÀ» ¼³Á¤ÇÕ´Ï´Ù. (0U ~ 255U)
   * @param r 
   * @param g 
   * @param b 
   * @param a 
   */
  void SetFontColor(char r, char g, char b, char a = 255U) {
    _textBrush.SetColor(Color(a, r, g, b));
  }

  /**
   * @brief ÆùÆ® ¼öÆò Á¤·ÄÀ» ¼³Á¤ÇÑ´Ù.
   * @param textHAlignmet LEFT, CENTER, or RIGHT
   */
  void SetTextHorizontalAlignment(H_DIRECTION textHAlignment) {
    switch (textHAlignment) {
      case H_DIRECTION::LEFT: {
        _textFormat.SetLineAlignment(StringAlignmentNear);
      } break;
      case H_DIRECTION::CENTER: {
        _textFormat.SetLineAlignment(StringAlignmentCenter);
      } break;
      case H_DIRECTION::RIGHT: {
        _textFormat.SetLineAlignment(StringAlignmentFar);
      } break;
    }
  } 

  /**
   * @brief ÆùÆ® ¼öÁ÷ Á¤·ÄÀ» ¼³Á¤ÇÑ´Ù.
   * @param textVJustification TOP, CENTER, or BOTTOM
   */
  void SetTextVerticalJustify(V_DIRECTION textVJustification) {
    switch (textVJustification) {
      case V_DIRECTION::TOP: {
        _textFormat.SetAlignment(StringAlignmentNear);
      } break;
      case V_DIRECTION::CENTER: {
        _textFormat.SetAlignment(StringAlignmentCenter);
      } break;
      case V_DIRECTION::BOTTOM: {
        _textFormat.SetAlignment(StringAlignmentFar);
      } break;
    }
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
		} else {
			auto it = _pSpriteRegister.find(tag);
			if (it == _pSpriteRegister.end())
        _currentSprite = nullptr;
			else 
				_currentSprite = it->second;
		}

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

		_caching && 
		_currentCachedBitmap && 
		g.DrawCachedBitmap(
      _currentCachedBitmap, 
      _currentSpriteRect->X,
      _currentSpriteRect->Y
    );

    // If no caching
    !_caching && 
		_currentSprite && 
		g.DrawImage(_currentSprite, *_currentSpriteRect);

		// Draw border if enabled
    _border && 
		//g.DrawRectangle(&_pen, *_currentSpriteRect);
		g.DrawRectangle(&_pen, _position.X, _position.Y,
		_currentSpriteRect->Width, _currentSpriteRect->Height);

		// Fill Rect if enabled
		_fill && 
		//g.FillRectangle(&_brush, *_currentSpriteRect);
		g.FillRectangle(&_brush, _position.X, _position.Y,
		_currentSpriteRect->Width, _currentSpriteRect->Height);

    // Draw Text
		
    !_text.empty() && 
		!g.TranslateTransform(_currentSpriteRect->X, _currentSpriteRect->Y) &&
		!g.DrawString(_text.c_str(), -1, _pFont, _textPosition, &_textFormat, &_textBrush) &&
		!g.TranslateTransform(-_currentSpriteRect->X, -_currentSpriteRect->Y);
	}

 private:
  /**
   * @brief ÇÇ¹þ Æ÷Áö¼Ç¿¡ ¸Â°Ô ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓÀ» Á¶Á¤ÇÕ´Ï´Ù.
   * @param sprite
   * @param spriteRect
   */
  void __AdjustSpriteRect(Bitmap* sprite, Rect& spriteRect) {
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
    CollectiveRenderable<T>::_pSpriteRegister;

template <class T>
std::unordered_map<std::wstring, CachedBitmap*>
    CollectiveRenderable<T>::_pSpriteCacheData;

#ifndef NDEBUG
inline CollectiveRenderable<int> CollectiveRenderableDebugTrigger;
#endif
