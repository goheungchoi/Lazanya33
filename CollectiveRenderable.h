#pragma once

#include "IRenderable.h"

template <class T>
class CollectiveRenderable : public IRenderable {
  static std::unordered_map<std::wstring, Bitmap*> _pSpriteRegister;
  static std::unordered_map<Bitmap*, CachedBitmap*> _pSpriteCacheData;

 protected:
  // Cache Data
  bool          _caching;
  Bitmap*       _currentSprite;
  CachedBitmap* _currentCachedBitmap;
  Rect*         _currentSpriteRect;
  std::wstring  _currentTag;

  // Sprite Frames
  std::unordered_map<Bitmap*, Rect> _spriteRects;  // The destination Rect

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
  CollectiveRenderable(bool caching = false) : 
    _caching{caching}, 
    _currentSprite{nullptr}, 
    _currentCachedBitmap{nullptr},
    _currentSpriteRect{nullptr},

    _textPosition(0.0f, 0.0f),
    _fontFamily(L"Arial"), 
    _font(&_fontFamily, 12, FontStyleRegular, UnitPixel),
    _textBrush(Color(255, 0, 0, 0)) {}

  CollectiveRenderable(int x, int y, bool caching = false)
  : IRenderable(x, y), CollectiveRenderable(caching) {}
  
  virtual ~CollectiveRenderable() {}

  /**
   * @brief ��������Ʈ�� �±׿� �Բ� �������� ������Ʈ�� ���ε� �մϴ�.
   * @param pSprite ���ε� �� ��������Ʈ ������
   */
  void BindSpriteWithTag(Bitmap* pSprite, const std::wstring& tag) {
    _pSpriteRegister[tag] = pSprite;

    Rect spriteRect(  // Create the destination rect
      _position.X, 
      _position.Y, 
      pSprite->GetWidth(), 
      pSprite->GetHeight()
    );

    // Adjust the sprite Rect following pivot positions
    __AdjustSpriteRect(pSprite, spriteRect);

    // ��������Ʈ �������� ����ϴ�.
    _spriteRects[pSprite] = std::move(spriteRect);
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
    for (auto& p : _pSpriteRegister) {
      __AdjustSpriteRect(p.second, _spriteRects[p.second]);
    }
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

  /**
   * @brief ���� ������ �ϰ� �ִ� ��������Ʈ�� �����͸� �����մϴ�.
   * @return ��������Ʈ�� ��Ʈ�� ������
   */
  Bitmap* GetCurrentSprite() { return _currentSprite; }

  /**
   * @brief �±׿� �´� ��������Ʈ�� ��ȯ�մϴ�. 
   * �� �Լ��� �ٸ� �Լ��鿡 �� ��������� ���� �� �ֽ��ϴ�.
   * @param tag ��������Ʈ �±�
   */
  void SetCurrentTag(const wchar_t* tag) {
    _currentTag.assign(tag);
    auto it = _pSpriteRegister.find(_currentTag);
    if (it == _pSpriteRegister.end()) {
      throw std::exception("CollectiveRenderer: Tag not found!");
    }

    //// Cache all necessary information for rendering.
    // Set the current sprite
    _currentSprite = it->second;
    // Set the current cached bitmap
    if (auto cacheIt = _pSpriteCacheData.find(_currentSprite); 
        cacheIt == _pSpriteCacheData.end()) // Check if the cached sprite exists
      _currentCachedBitmap = nullptr;  // If not, mark this sprite has no cache.
    else
      _currentCachedBitmap = cacheIt->second;
    // Set the current frame
    _currentSpriteRect = &_spriteRects[_currentSprite];
  }

  /**
   * @brief
   * @param g
   */
  void Render(Gdiplus::Graphics& g) override {
    if (_caching) {
      // Check if the cached bitmap of the current sprite exists
      if (!_currentCachedBitmap) {
        // If not, create one.
        _currentCachedBitmap = new CachedBitmap(_currentSprite, &g);
        _pSpriteCacheData[_currentSprite] = _currentCachedBitmap;
      }
      g.DrawCachedBitmap(
        _currentCachedBitmap, 
        _currentSpriteRect->X,
        _currentSpriteRect->Y
      );
    } else {
      // If no caching
      g.DrawImage(_currentSprite, *_currentSpriteRect);
    }

    // Draw Text
    if (!_text.empty()) {
      g.DrawString(_text.c_str(), -1, &_font, _textPosition, &_textFormat, &_textBrush);
    }

#ifndef NDEBUG  // ������� ��, ����׿� �簢���� �׸�.
    Pen debuggingPen(Color::Red, 5.f);
    g.DrawRectangle(&debuggingPen, *_currentSpriteRect);
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

template <class T>
std::unordered_map<std::wstring, Bitmap*>
    CollectiveRenderable<T>::_pSpriteRegister;
