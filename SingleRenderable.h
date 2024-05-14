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
	* @brief ��������Ʈ�� �� �������� ������Ʈ�� ���ε��Ѵ�.
	* @param pSprite ���ε� �� ��������Ʈ ������
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

		// ��������Ʈ �������� ����ϴ�.
		_spriteRect = std::move(spriteRect);
	}

	/**
   * @brief ��������Ʈ �������� �������� ����� �ǹ� �����ǿ� �°� ������Ʈ
   * �մϴ�.
   * @param horizontal ���� �ǹ� ������
   * @param vertical ���� �ǹ� ������
   */
  void UpdateSpritePivotPosition(H_DIRECTION horizontal, V_DIRECTION vertical) {
    _horizontal = horizontal;
    _vertical = vertical;
    __AdjustSpriteRect(_pSprite, _spriteRect);

  }
	
  /**
   * @brief �� ������Ʈ�� ǥ���� �ؽ�Ʈ�� �����Ѵ�.
   */
  void SetText(const wchar_t* text) { _text.assign(text); }
  void SetTextPosition(float x, float y) { _textPosition = {x, y}; }

  /**
   * @brief �ؽ�Ʈ�� ��������Ʈ ������ �ȿ����� ����� ��ġ�� �����Ѵ�.
   * @return ����� ��ġ�� X��
   */
  float GetTextPositionX() { return _textPosition.X; }
  /**
   * @brief �ؽ�Ʈ�� ��������Ʈ ������ �ȿ����� ����� ��ġ�� �����Ѵ�.
   * @return ����� ��ġ�� Y��
   */
  float GetTextPositionY() { return _textPosition.Y; }
  /**
   * @brief �ؽ�Ʈ�� ��������Ʈ ������ �ȿ����� ����� ��ġ�� �����Ѵ�.
   * @return PointF ��Ʈ����
   */
  PointF GetTextPosition() { return _textPosition; }

  /**
   * @brief ��Ʈ �йи��� �����մϴ�.
   * @param fontFamily ��Ʈ �йи�, ����) L"Arial"
   */
  void SetFontFamily(const char* fontFamily) {
    _fontFamily = FontFamily(fontFamily);
  }

  /**
   * @brief �ؽ�Ʈ�� ��Ʈ�� �����Ѵ�.
   * @param fontSize �ȼ� ���� ��Ʈ ������
   * @param fontStyle ��Ʈ ��Ÿ��, �⺻�� = Regular
   * @param unit ��Ʈ ����, �⺻�� = Pixel
   */
  void SetFont(int fontSize, FontStyle fontStyle = FontStyleRegular,
               Unit unit = UnitPixel) {
    _font = Font(&_fontFamily, fontSize, fontStyle, unit);
  }

  /**
   * @brief �ؽ�Ʈ�� ������ �����մϴ�. (0U ~ 255U)
   * @param r 
   * @param g 
   * @param b 
   * @param a 
   */
  void SetFontColor(char r, char g, char b, char a = 255U) {
    _textBrush.SetColor(Color(a, r, g, b));
  }

  /**
   * @brief ��Ʈ ���� ������ �����Ѵ�.
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
   * @brief ��Ʈ ���� ������ �����Ѵ�.
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

#ifndef NDEBUG	// ������� ��, ����׿� �簢���� �׸�.
		Pen debuggingPen(Color::Red, 5.f);
		g.DrawRectangle(&debuggingPen, _spriteRect);
#endif
	}

private:
	/**
   * @brief �ǹ� �����ǿ� �°� ��������Ʈ �������� �����մϴ�.
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
