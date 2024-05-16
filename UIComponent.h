#pragma once

#include "IRenderable.h"

// TODO: Need to handle some player interaction (button - mouse hover)
// TODO: Might need some loop animations

// UIComponent can inherit from either SingleRenderable or CollectiveRenderable

enum class PositionLayout {
	LAYOUT_STATIC,
	LAYOUT_ABSOLUTE,
	LAYOUT_FIXED,
	LAYOUT_RELATIVE
};


/**
 * @brief UI component base class. 
 * If you need faster rendering sprites, might consider
 * using SingleRenderable or CollectiveRenderable.
 */
class UIComponent : public IRenderable {
protected:
// UIComponent Hierarchy 
	UIComponent* _parentComponent{nullptr};
	std::list<UIComponent*> _childComponents;

public:
	void AddChildComponent(UIComponent* child) {
		child->_parentComponent = this;
		_childComponents.push_back(child);
	}

	void RemoveChildComponent(UIComponent* child) {
		child->_parentComponent = nullptr;
		_childComponents.remove(child);
	}
	
// Graphics Utilities
protected:
	// Contains X, Y coordinate, and Width and Height
	int& _x, _y;
	int _width, _height;

	Matrix _transform;
	PointF pivot{0.f, 0.f};

	bool _border{false};
  Pen _pen;

  bool _fill{false};
  SolidBrush _brush;

	Image* _pImage{nullptr};

public:
// Transform Utilities
	int GetX() { return _x; }
	int GetY() { return _y; }
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
	int GetCenterX() { return _x + (_width >> 1); }
	int GetCenterY() { return _y + (_height >> 1); }

	Matrix& GetTransform() { return _transform; }

	void Scale(float x, float y) {
		_transform.Scale(x, y);
	}

	void SetRotationPivot(float x, float y) {
		pivot = {x, y};
	}

	void Rotate(float degree) {
		_transform.RotateAt(degree, pivot);
	}

	void Rotate(float degree, PointF pivot) { 
		_transform.RotateAt(degree, pivot);
	}

	void Translate(float x, float y) { 
		_transform.Translate(x, y);
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
		_pen.SetColor(Color(a, r, g, b));
    _pen.SetWidth(width);
	}
	void EnableBorder(bool enable) { _border = enable; }
	void DisableBorder(bool disable) { _border = disable; }

	/**
	 * @brief Set fill color of this sprite
	 * @param r Red value from 0~255
	 * @param g Green value from 0~255
	 * @param b Blue value from 0~255
	 * @param a Alpha value from 0~255. Default is 255.
	 */
	void SetFillColor(char r, char g, char b, char a = 255U) {
		_brush.SetColor(Color(a, r, g, b));
	}
	void EnableFill(bool enable) { _fill = enable; }
	void DisableFill(bool disable) { _fill = disable; }

	void SetImage(Image* image) {
		_pImage = image;
	}

// Text Utilities
protected:
	// Text Data
  std::wstring    _text;
  PointF          _textPosition;
  FontFamily*     _pFontFamily;
  Font*           _pFont;
  StringFormat    _textFormat;  // Text alignment
  SolidBrush      _textBrush;  // Color of the text

public:
	/**
   * @brief Set text to be displayed on this component
   */
  void SetText(const wchar_t* text) { _text.assign(text); }

  /**
   * @brief Set relative text position
   * @param x X coordinate
   * @param y Y coordinate
   */
  void SetTextPosition(float x, float y) { _textPosition = {x, y}; }

  /**
   * @brief Get the X value of the text relative position.
   * @return float X position
   */
  float GetTextPositionX() { return _textPosition.X; }
  /**
   * @brief Get the Y value of the text relative position.
   * @return float X position
   */
  float GetTextPositionY() { return _textPosition.Y; }
  /**
   * @brief Get the relative position of the text
   * @return PointF PointF struct containing the position
   */
  PointF GetTextPosition() { return _textPosition; }

  /**
   * @brief Set font family
   * @param fontFamily font family name e.i. L"Arial"
   */
  void SetFontFamily(const wchar_t* fontFamily) {
    if (_pFontFamily) delete _pFontFamily;
    _pFontFamily = new FontFamily(fontFamily);
  }

  /**
   * @brief Set font properties
   * @param fontSize font size
   * @param fontStyle font style e.i. Regular, Bold, Italic ...
   * @param unit Unit of the font e.i. pixel, inch, cm ...
   */
  void SetFont(int fontSize, FontStyle fontStyle = FontStyleRegular,
               Unit unit = UnitPixel) {
    _pFont = new Font(_pFontFamily, fontSize, fontStyle, unit);
  }

  /**
   * @brief Set font color (0U ~ 255U)
   * @param r 
   * @param g 
   * @param b 
   * @param a 
   */
  void SetFontColor(char r, char g, char b, char a = 255U) {
    _textBrush.SetColor(Color(a, r, g, b));
  }

  /**
   * @brief Set horizontal alignment of the text
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
   * @brief Set vertical justification of the text
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

// Position Layout Utilities
private:
	PositionLayout _positionLayout{PositionLayout::LAYOUT_STATIC};

public:
	void SetPositionLayout(PositionLayout posLayout) {
		_positionLayout = posLayout;
	}

	PositionLayout GetPositionLayout() {
		return _positionLayout;
	}

public:
	UIComponent(int x, int y, int w, int h) : 
		IRenderable(x, y), 
		_x{_position.X},
    _y{_position.Y},
    _width{w},
    _height{h},

		// Graphics
		_pen(Color(0, 0, 0)),
		_brush(Color(0, 0, 0)),

		// Text properties
		// _text("")
    _textPosition(0.f, 0.f),
    _pFontFamily(new FontFamily(L"Arial")), 
    _pFont(new Font(_pFontFamily, 12, FontStyleRegular, UnitPixel)),
    // _textFormat(StringAlignmentNear, StringAlignmentNear)
		_textBrush(Color(255, 0, 0, 0)) {}
	
	// Change appearance, e.g., highlight
	virtual void OnMouseEnter() {};

	// Revert appearance
  virtual void OnMouseLeave() {};

	// Maybe show as pressed
  virtual void OnMouseDown() {};

	// Perform action
  virtual void OnMouseUp() {};

public:
	// Default Render
	void DefaultRender(Graphics& g) {
		// Set Transform
		g.MultiplyTransform(&_transform);

		// Draw image if exists
		_pImage && 
		g.DrawImage(_pImage, _x, _y, _width, _height);

		// TODO: When drawing borders,
		// Don't apply scaling
		// Draw border if enabled

		_border && 
		//g.DrawRectangle(&_pen, *_currentSpriteRect);
		g.DrawRectangle(&_pen, _x, _y, _width, _height);

		// Fill Rect if enabled
		_fill && 
		//g.FillRectangle(&_brush, *_currentSpriteRect);
		g.FillRectangle(&_brush, _x, _y, _width, _height);

		
		// Draw Text
		!_text.empty() && 
		!g.TranslateTransform(_x, _y) &&
		!g.DrawString(_text.c_str(), -1, _pFont, _textPosition, &_textFormat, &_textBrush) &&
		!g.TranslateTransform(-_x, -_y);

		RenderChildren(g);

		// Reset Transform
		Matrix* mClone = _transform.Clone();
		mClone->Invert();
		g.MultiplyTransform(mClone);
	}

	// Render
	virtual void Render(Graphics& g) override {
		if (!_parentComponent) {
			DefaultRender(g);
			return;
		}

		switch (_positionLayout) {
			case PositionLayout::LAYOUT_STATIC: {
				// Ignore the position of itself, 
				// but follow the layout of the parent
				
				// Draw image if exists
				_pImage && 
				g.DrawImage(_pImage, 0, 0, _width, _height);

				// TODO: When drawing borders,
				// Don't apply scaling
				// Draw border if enabled

				_border && 
				//g.DrawRectangle(&_pen, *_currentSpriteRect);
				g.DrawRectangle(&_pen, 0, 0, _width, _height);

				// Fill Rect if enabled
				_fill && 
				//g.FillRectangle(&_brush, *_currentSpriteRect);
				g.FillRectangle(&_brush, 0, 0, _width, _height);

				// Draw Text
				!_text.empty() && 
				g.DrawString(_text.c_str(), -1, _pFont, _textPosition, &_textFormat, &_textBrush);
  
				RenderChildren(g);

			} break;
			case PositionLayout::LAYOUT_ABSOLUTE: {
				// Use the absolute screen coordinate
				// Reset the global transformation
				Matrix tmp;
				g.GetTransform(&tmp);
				g.SetTransform(&_transform);

				// Draw
				// 
				// Draw image if exists
				_pImage && 
				g.DrawImage(_pImage, _x, _y, _width, _height);

				// TODO: When drawing borders,
				// Don't apply scaling
				// Draw border if enabled

				_border && 
				//g.DrawRectangle(&_pen, *_currentSpriteRect);
				g.DrawRectangle(&_pen, _x, _y, _width, _height);

				// Fill Rect if enabled
				_fill && 
				//g.FillRectangle(&_brush, *_currentSpriteRect);
				g.FillRectangle(&_brush, _x, _y, _width, _height);

				// Draw Text
				!_text.empty() && 
				!g.TranslateTransform(_x, _y) &&
				!g.DrawString(_text.c_str(), -1, _pFont, _textPosition, &_textFormat, &_textBrush) &&
				!g.TranslateTransform(-_x, -_y);

				RenderChildren(g);

				// Restore the global transformation
				g.SetTransform(&tmp);

			} break;
			case PositionLayout::LAYOUT_FIXED: {
				// Set the relatively fixed position
				// Will be checked by the parent
			}
			case PositionLayout::LAYOUT_RELATIVE: {
				// Passively relatively placed x, y 
				DefaultRender(g);
			} break;
		}
	}

	virtual void RenderChildren(Graphics& g) override {
		for (UIComponent* pChildComp : _childComponents) {
			g.TranslateTransform(_x, _y);
			pChildComp->Render(g);
			g.TranslateTransform(-_x, -_y);
		}
	}
};

