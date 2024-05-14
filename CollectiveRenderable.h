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
	* @brief ��������Ʈ�� �� �������� ������Ʈ�� ���ε��Ѵ�.
	* @param pSprite ���ε� �� ��������Ʈ ������
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
	//void SetFont(
	//	const wchar_t* fontFamily, 
	//	int fontSize, 
	//	// TODO: ������ ��Ʈ ������ ������ �� �ְ� �ϱ�.
	//	FontStyle fontStyle = FontStyleRegular,
	//	Unit unit = UnitPixel
	//) {
	//	FontFamily fontFamily(fontFamily);
	//	_font = Font(&fontFamily, fontSize, fontStyle, unit);
	//}

	/**
	* @brief ��Ʈ ������ �����Ѵ�.
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
		
#ifndef NDEBUG	// ������� ��, ����׿� �簢���� �׸�.
		Pen debuggingPen(Color::Red, 5.f);
		g.DrawRectangle(&debuggingPen, _spriteRect);
#endif
	}
};

template<class T>
std::unordered_map<std::wstring, Bitmap*> CollectiveRenderable<T>::_pSpriteRegister;
