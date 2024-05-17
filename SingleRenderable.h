#pragma once

#include "IRenderable.h"

using namespace Gdiplus;

template<class T>
class SingleRenderable : public IRenderable {
public:
	static Bitmap* _pSprite;
  static CachedBitmap* _pSpriteCache;

protected:
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

	// Text Data
  std::wstring    _text;
  PointF          _textPosition;
  FontFamily*     _pFontFamily;
  Font*           _pFont;
  StringFormat    _textFormat;  // Text alignment
  SolidBrush      _textBrush;  // Color of the text


public:
	SingleRenderable(bool caching = true) : 
		_caching{caching},

		// Graphics
    _pen(Color(0, 0, 0)),
    _brush(Color(0, 0, 0)),

		_textPosition(0.0f, 0.0f),
		_pFontFamily(new FontFamily(L"Arial")), 
		_pFont(new Font(_pFontFamily, 12, FontStyleRegular, UnitPixel)),
		_textBrush(Color(255, 0, 0, 0)) {}

	SingleRenderable(int x, int y, bool caching = true) 
		: IRenderable(x, y), SingleRenderable(caching) {}

  /**
   * @brief 임의의 프레임 포지션과 너비, 높이를 지정합니다.
   * @param x 
   * @param y 
   * @param w 
   * @param h 
   * @param caching 
   */
  SingleRenderable(int x, int y, int w, int h, bool caching = true) 
		: IRenderable(x, y), SingleRenderable(caching), _spriteRect(x, y, w, h) {}

	virtual ~SingleRenderable() {}

	/**
	* @brief ½ºÇÁ¶óÀÌÆ®¸¦ ÀÌ ·»´õ·¯ºí ¿ÀºêÁ§Æ®¿¡ ¹ÙÀÎµùÇÑ´Ù.
	* @param pSprite ¹ÙÀÎµù ÇÒ ½ºÇÁ¶óÀÌÆ® Æ÷ÀÎÅÍ
	*/
	void BindSprite(Bitmap* pSprite) { 
		_pSprite = pSprite; 

		Rect spriteRect(  // Create the destination rect
      _position.X, 
      _position.Y, 
      pSprite->GetWidth(), 
      pSprite->GetHeight()
    );

		// Adjust the sprite Rect following pivot positions
		__AdjustSpriteRect(pSprite, spriteRect);

		// ½ºÇÁ¶óÀÌÆ® ÇÁ·¹ÀÓÀ» ´ã½À´Ï´Ù.
		_spriteRect = std::move(spriteRect);
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
  void SetTextVerticalJustify(H_DIRECTION textVJustification) {
    switch (textVJustification) {
      case H_DIRECTION::TOP: {
        _textFormat.SetAlignment(StringAlignmentNear);
      } break;
      case H_DIRECTION::CENTER: {
        _textFormat.SetAlignment(StringAlignmentCenter);
      } break;
      case H_DIRECTION::BOTTOM: {
        _textFormat.SetAlignment(StringAlignmentFar);
      } break;
    }
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

	virtual void Render(Graphics& g) override {

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

		// Draw Text
		
    !_text.empty() && 
		!g.TranslateTransform(_spriteRect.X, _spriteRect.Y) &&
		!g.DrawString(_text.c_str(), -1, _pFont, _textPosition, &_textFormat, &_textBrush) &&
		!g.TranslateTransform(-_spriteRect.X, -_spriteRect.Y);
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

template<class T>
Bitmap* SingleRenderable<T>::_pSprite{ nullptr };

template<class T>
CachedBitmap* SingleRenderable<T>::_pSpriteCache{ nullptr };

#ifndef NDEBUG
inline SingleRenderable<int> SingleRenderableDebugTrigger;
#endif
