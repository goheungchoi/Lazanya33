#pragma once

#include "IRenderable.h"

template<class T>
class SingleRenderable : public IRenderable {
	static Bitmap* _pSprite;
  static CachedBitmap* _pSpriteCache;

protected:
	// Cache Data
  bool _caching;
	Rect _spriteRect;	// The destination Rect

	// Pivot Position
  H_DIRECTION _horizontal{H_DIRECTION::LEFT};
  V_DIRECTION _vertical{V_DIRECTION::TOP};

	// Text Data
  std::wstring    _text;
  PointF          _textPosition;
  FontFamily      _fontFamily;
  Font            _font;
  StringFormat    _textFormat;  // Text alignment
  SolidBrush      _textBrush;  // Color of the text


public:
	SingleRenderable(bool caching = false) : 
		_caching{caching},

		_textPosition(0.0f, 0.0f),
		_fontFamily(L"Arial"), 
		_font(&_fontFamily, 12, FontStyleRegular, UnitPixel),
		_textBrush(Color(255, 0, 0, 0)) {}

	SingleRenderable(int x, int y, bool caching = false) 
		: IRenderable(x, y), SingleRenderable(caching) {}

	virtual ~SingleRenderable() {}

	/**
	* @brief 스프라이트를 이 렌더러블 오브젝트에 바인딩한다.
	* @param pSprite 바인딩 할 스프라이트 포인터
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

		// 스프라이트 프레임을 담습니다.
		_spriteRect = std::move(spriteRect);
	}

	/**
   * @brief 스프라이트 프레임의 포지션을 변경된 피벗 포지션에 맞게 업데이트
   * 합니다.
   * @param horizontal 수평 피벗 포지션
   * @param vertical 수직 피벗 포지션
   */
  void UpdateSpritePivotPosition(H_DIRECTION horizontal, V_DIRECTION vertical) {
    _horizontal = horizontal;
    _vertical = vertical;
    __AdjustSpriteRect(_pSprite, _spriteRect);

  }
	
  /**
   * @brief 이 오브젝트가 표시할 텍스트를 설정한다.
   */
  void SetText(const wchar_t* text) { _text.assign(text); }
  void SetTextPosition(float x, float y) { _textPosition = {x, y}; }

  /**
   * @brief 텍스트의 스프라이트 프레임 안에서의 상대적 위치를 리턴한다.
   * @return 상대적 위치의 X값
   */
  float GetTextPositionX() { return _textPosition.X; }
  /**
   * @brief 텍스트의 스프라이트 프레임 안에서의 상대적 위치를 리턴한다.
   * @return 상대적 위치의 Y값
   */
  float GetTextPositionY() { return _textPosition.Y; }
  /**
   * @brief 텍스트의 스프라이트 프레임 안에서의 상대적 위치를 리턴한다.
   * @return PointF 스트럭쳐
   */
  PointF GetTextPosition() { return _textPosition; }

  /**
   * @brief 폰트 패밀리를 설정합니다.
   * @param fontFamily 폰트 패밀리, 예시) L"Arial"
   */
  void SetFontFamily(const char* fontFamily) {
    _fontFamily = FontFamily(fontFamily);
  }

  /**
   * @brief 텍스트의 폰트를 설정한다.
   * @param fontSize 픽셀 단위 폰트 사이즈
   * @param fontStyle 폰트 스타일, 기본값 = Regular
   * @param unit 폰트 단위, 기본값 = Pixel
   */
  void SetFont(int fontSize, FontStyle fontStyle = FontStyleRegular,
               Unit unit = UnitPixel) {
    _font = Font(&_fontFamily, fontSize, fontStyle, unit);
  }

  /**
   * @brief 텍스트의 색깔을 설정합니다. (0U ~ 255U)
   * @param r 
   * @param g 
   * @param b 
   * @param a 
   */
  void SetFontColor(char r, char g, char b, char a = 255U) {
    _textBrush.SetColor(Color(a, r, g, b));
  }

  /**
   * @brief 폰트 수평 정렬을 설정한다.
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
   * @brief 폰트 수직 정렬을 설정한다.
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

	void Render(Gdiplus::Graphics& g) override {
    if (_caching) {
      // Check if the cached bitmap of the current sprite exists
      if (!_pSpriteCache) {
        // If not, create one.
        _pSpriteCache = new CachedBitmap(_pSprite, &g);
      }
      g.DrawCachedBitmap(
        _pSpriteCache, 
        _spriteRect->X,
        _spriteRect->Y
      );
    } else {
      // If no caching
      g.DrawImage(_pSprite, _spriteRect);
    }

		// Draw Text
    if (!_text.empty()) {
      g.DrawString(_text.c_str(), -1, &_font, _textPosition, &_textFormat, &_textBrush);
    }

#ifndef NDEBUG	// 디버깅일 때, 디버그용 사각형을 그림.
		Pen debuggingPen(Color::Red, 5.f);
		g.DrawRectangle(&debuggingPen, _spriteRect);
#endif
	}

private:
	/**
   * @brief 피벗 포지션에 맞게 스프라이트 프레임을 조정합니다.
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
