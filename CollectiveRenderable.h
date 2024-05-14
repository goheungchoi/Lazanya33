#pragma once

#include "IRenderable.h"

enum H_DIRECTION {
  LEFT    = 0b0001,
  RIGHT   = 0b0010,
  CENTER  = 0b0011,
};

enum V_DIRECTION { 
  TOP     = 0b0100, 
  CENTER  = 0b1100, 
  BOTTOM  = 0b1000 
};

template <class T>
class CollectiveRenderable : public IRenderable {
  static std::unordered_map<std::wstring, Bitmap*> _pSpriteRegister;
  static std::unordered_map<Bitmap*, CachedBitmap*> _pSpriteCacheData;

  // static std::optional<CachedBitmap> _spriteCache;

 protected:
  bool _caching;
  Bitmap* _currentSprite;
  std::wstring _currentTag;
  std::unordered_map<Bitmap*, Rect> _spriteRects;  // The destination Rect

  // Pivot position
  H_DIRECTION _horizontal;
  V_DIRECTION _vertical;

  // Text Data
  /*std::wstring _text;
  PointF _textOrigin;
  FontFamily _fontFamily;
  Font _font;
  StringFormat _textFormat;
  SolidBrush _textBrush{Color(255, 0, 0, 0)};*/

 public:
  CollectiveRenderable() : _caching{false} {}
  CollectiveRenderable(int x, int y, bool caching = false) 
    : IRenderable(x, y), _caching{caching} {}
  virtual ~CollectiveRenderable() {}

  /**
   * @brief ��������Ʈ�� �� �������� ������Ʈ�� ���ε� �մϴ�.
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
   * @brief ��������Ʈ �������� �������� ����� �ǹ� �����ǿ� �°� ������Ʈ �մϴ�.
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
  /*void SetText(const wchar_t* text, float x, float y) {
          _text.assign(text);
          _textOrigin = {x, y};
  }*/ // TODO: Proper handle of wstring!

  /**
   * @brief �ؽ�Ʈ�� ��Ʈ�� �����Ѵ�.
   * @param fontFamily ��Ʈ �йи�, ����) L"Arial"
   * @param fontSize �ȼ� ���� ��Ʈ ������
   * @param fontStyle ��Ʈ ��Ÿ��, �⺻�� = Regular
   * @param unit ��Ʈ ����, �⺻�� = Pixel
   */
  // void SetFont(
  //	const wchar_t* fontFamily,
  //	int fontSize,
  //	// TODO: ������ ��Ʈ ������ ������ �� �ְ� �ϱ�.
  //	FontStyle fontStyle = FontStyleRegular,
  //	Unit unit = UnitPixel
  //) {
  //	FontFamily fontFamily(fontFamily);
  //	_font = Font(&fontFamily, fontSize, fontStyle, unit);
  // }

  /**
   * @brief ��Ʈ ������ �����Ѵ�.
   */
  void SetTextAlignment() {}  // TODO:

  /**
   * @brief 
   * @return 
   */
  Bitmap* GetSprite() { return _pSprite; }

  void SetCurrentTag(const wchar_t* tag) {
    _currentTag.assign(tag);
    auto& it = _currentSprite[tag];
  }

  /**
   * @brief 
   * @param g 
   */
  void Render(Gdiplus::Graphics& g) override {
    if (caching) {
      
    
    }


        /*unsigned int x = _spriteRects[p.second].X;
        unsigned int y = _spriteRects[p.second].Y;
        g.DrawCachedBitmap(p.second, )*/


    if (_pSprite) {
      // if (!_spriteCache) {
      //_spriteCache = CachedBitmap(_pSprite, &g);
      //}

      // g.DrawCachedBitmap(&(*_spriteCache), _position.X, _position.Y);
    }

    // if (!_text.empty())
    // g.DrawString(_text.c_str(), -1, &_font, _textOrigin, &_textFormat);

#ifndef NDEBUG  // ������� ��, ����׿� �簢���� �׸�.
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
      case LEFT: {
      } break;
      case CENTER: {
        frameX -= halfW;
      } break;
      case RIGHT: {
        frameX -= width;
      } break;
    }

    switch (_vertical) {
      case TOP: {
      } break;
      case CENTER: {
        frameY -= halfH;
      } break;
      case BOTTOM: {
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
