#pragma once

#include "IRenderable.h"

template<class T>
class CollectiveRenderable : public IRenderable {
	static std::unordered_map<std::wstring, Bitmap*> _pSpriteRegister;
	//static std::optional<CachedBitmap> _spriteCache;

protected:
	std::unordered_map<Bitmap*, Rect> _spriteRects;	// The destination Rect
	/*std::wstring _text;
	PointF _textOrigin;
	FontFamily _fontFamily;
	Font _font;
	StringFormat _textFormat;
	SolidBrush _textBrush{Color(255, 0, 0, 0)};*/


public:
	CollectiveRenderable() {};
	CollectiveRenderable(int x, int y) 
		: IRenderable(x, y), _spriteRect(x, y, 500, 500) {
	}
	virtual ~SingleRenderable() {};

	/**
	* @brief 스프라이트를 이 렌더러블 오브젝트에 바인딩한다.
	* @param pSprite 바인딩 할 스프라이트 포인터
	*/
	void BindSprite(Bitmap* pSprite) { 
		_pSprite = pSprite; 
		_spriteRect = Rect(	// Create the destination rect
			_position.X, 
			_position.Y, 
			pSprite->GetWidth(), 
			pSprite->GetHeight()
		);
	}

	/**
	* @brief 이 오브젝트가 표시할 텍스트를 설정한다.
	*/
	/*void SetText(const wchar_t* text, float x, float y) { 
		_text.assign(text); 
		_textOrigin = {x, y};
	}*/ // TODO: Proper handle of wstring!

	/**
	* @brief 텍스트의 폰트를 설정한다.
	* @param fontFamily 폰트 패밀리, 예시) L"Arial"
	* @param fontSize 픽셀 단위 폰트 사이즈 
	* @param fontStyle 폰트 스타일, 기본값 = Regular
	* @param unit 폰트 단위, 기본값 = Pixel
	*/
	//void SetFont(
	//	const wchar_t* fontFamily, 
	//	int fontSize, 
	//	// TODO: 유저가 폰트 색깔을 지정할 수 있게 하기.
	//	FontStyle fontStyle = FontStyleRegular,
	//	Unit unit = UnitPixel
	//) {
	//	FontFamily fontFamily(fontFamily);
	//	_font = Font(&fontFamily, fontSize, fontStyle, unit);
	//}

	/**
	* @brief 폰트 정렬을 설정한다.
	*/
	void SetTextAlignment() {}	// TODO:

	Bitmap* GetSprite() { return _pSprite; }

	void Render(Gdiplus::Graphics& g) override {
		if (_pSprite) {
			//if (!_spriteCache) {
				//_spriteCache = CachedBitmap(_pSprite, &g);
			//}
			
			//g.DrawCachedBitmap(&(*_spriteCache), _position.X, _position.Y);
		}

		//if (!_text.empty())
			//g.DrawString(_text.c_str(), -1, &_font, _textOrigin, &_textFormat);
		
#ifndef NDEBUG	// 디버깅일 때, 디버그용 사각형을 그림.
		Pen debuggingPen(Color::Red, 5.f);
		g.DrawRectangle(&debuggingPen, _spriteRect);
#endif
	}
};

template<class T>
std::unordered_map<std::wstring, Bitmap*> CollectiveRenderable<T>::_pSpriteRegister;
