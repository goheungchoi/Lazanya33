#pragma once

#include "IRenderable.h"

class IAnimation : public IRenderable {
public:
	IAnimation(int x, int y) : IRenderable(x, y) {}
	virtual ~IAnimation() {}
	virtual void Trigger() = 0;
	virtual void Reset() = 0;
	virtual bool IsPlaying() = 0;
	virtual void Update(double) = 0;
};

class Animation : public IAnimation {
	int& _x;
	int& _y;
	int _totalWidth, _totalHeight;

	bool _border{false};
  Pen _pen;

  bool _fill{false};
  SolidBrush _brush;

  Bitmap* _spriteSheet;
	std::vector<Rect> _frames;  // Frames in the sprite sheet
	std::vector<double> _frameDurations;

	double _currentFrameTime{ 0 };
	int _currentFrameIndex{ 0 };

	bool _isActive{ false };
  bool _isLoop;

public:
	Animation(Bitmap* spriteSheet, int x, int y, bool isLoop = false)
		: IAnimation(x, y), 
		_x{_position.X},
    _y{_position.Y},
		_spriteSheet{ spriteSheet }, _isLoop{ isLoop },
		// Graphics
		_pen(Color(0, 0, 0)),
		_brush(Color(0, 0, 0)) {
		if (!spriteSheet)
			throw std::invalid_argument("Animation: Sprite sheet is null!");
		_totalWidth = spriteSheet->GetWidth();
		_totalHeight = spriteSheet->GetHeight();
	}

	int GetX() { return _x; }
	void SetX(int x) { _x = x; }
	int GetY() { return _y; }
	void SetY(int y) { _y = y; }

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
	void SetBorderLineJoin(LineJoin lineJoin) {
		_pen.SetLineJoin(lineJoin);
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

	/**
	 * @brief Slice the sprite sheet, and set frame durations to be 1 sec.
	 * @param pixelSizeX 
	 * @param pixelSizeY 
	 * @param offsetX Slicing start point offset-x from the upper left corner.
	 * @param offsetY Slicing start point offset-y from the upper left corner.
	 * @param paddingX 
	 * @param paddingY 
	 */
	void SliceSpriteSheet(
		int pixelSizeX, int pixelSizeY,
		int offsetX, int offsetY,
		int paddingX, int paddingY
	) {
		int newTotalWidth = _totalWidth - offsetX;
		int newTotalHeight = _totalHeight - offsetY;

		int nrows = newTotalHeight / (pixelSizeY + paddingY);
		int ncols = newTotalWidth / (pixelSizeX + paddingX);

		_frames.resize(nrows * ncols);
		_frameDurations.resize(nrows * ncols, 1.0);

		auto idx = [&ncols](int row, int col) -> int {
			return col + row * ncols;
		};

		for (int i = 0; i < nrows; ++i) {
			for (int j = 0; j < ncols; ++j) {
				_frames[idx(i, j)] = Rect{
					offsetX + (pixelSizeX + paddingX) * j, // X
					offsetY + (pixelSizeY + paddingY) * i, // Y
					// Width    // Height
					pixelSizeX, pixelSizeY
				};
			}
		}
	}

	void SetFrameDurations(std::initializer_list<double> durations) {
		auto it = durations.begin();
		for (double& duration : _frameDurations) {
			if (it == durations.end()) --it;
			duration = *it;
			++it;
		}
	}

	void Trigger() override {
		_isActive = true;
		_currentFrameIndex = 0;
	}

	void Reset() override {
		_isActive = false;
		_currentFrameIndex = 0;
	}

	bool IsPlaying() override { return _isActive; }

  void Update(double dt) override {
		if (!_isActive) return;

    _currentFrameTime += dt;
    if (_currentFrameTime >= _frameDurations[_currentFrameIndex]) {
			_currentFrameTime -= _frameDurations[_currentFrameIndex];
			
			_currentFrameIndex++;
			if (_currentFrameIndex >= _frames.size()) {
				if (_isLoop) {
					_currentFrameIndex = 0;
				} else {
					_currentFrameIndex -= 1;
					_isActive = false;
				}
			}
    }
  }

	void Render(Graphics& g) override {
		if (!_isActive || !_spriteSheet) return;
		// Render the current frame from the sprite sheet;

		//Image image(L"Apple.gif");
		//UINT width = image.GetWidth();
		//UINT height = image.GetHeight();
		//// Make the destination rectangle 30 percent wider and
		//// 30 percent taller than the original image.
		//// Put the upper-left corner of the destination
		//// rectangle at (150, 20).
		//Rect destinationRect(150, 20, 1.3 * width, 1.3 * height);
		//// Draw a portion of the image. Scale that portion of the image
		//// so that it fills the destination rectangle.
		//graphics.DrawImage(
		//	 &image,
		//	 destinationRect,
		//	 0, 0,              // upper-left corner of source rectangle
		//	 0.75 * width,      // width of source rectangle
		//	 0.75 * height,     // height of source rectangle
		//	 UnitPixel);
		//}

		Rect& srcRect = _frames[_currentFrameIndex];

		Rect destRect = { _x, _y, srcRect.Width, srcRect.Height };

		g.DrawImage(
			_spriteSheet,
			destRect,
			srcRect.X,
			srcRect.Y,
			srcRect.Width,
			srcRect.Height,
			UnitPixel
		);
	}
};

class CubicBezier {
	double _x1, _y1;
	double _x2, _y2;
public:
	CubicBezier(double x1, double y1, double x2, double y2)
		: _x1{ x1 }, _y1{ y1 }, _x2{ x2 }, _y2{ y2 } {
		if (!((0 <= x1 && x1 <= 1) && (0 <= x2 && x2 <= 1)))
			throw std::invalid_argument("x1 and x2 should be between 0 and 1!");
	}

	/**
	 * @brief 
	 * @param t Interpolated time t from 0 to 1
	 * @return 
	 */
	double operator()(double t) {
		double s = 1.0 - t;
		double s_squared = s * s;

		double t_squared = t * t;
		double t_cubed = t_squared * t;

		double res1 = 3.0 * s_squared * t					* _y1;
		double res2 = 3.0 * s					* t_squared * _y2;

		return res1 + res2 + t_cubed;
	}
};

namespace bezier {
	static const CubicBezier linear{ 0.0, 0.0, 1.0, 1.0 };
	static const CubicBezier ease{ 0.25, 0.1, 0.25, 1.0 };
	static const CubicBezier ease_in{ 0.42, 0, 1.0, 1.0 };
	static const CubicBezier ease_out{ 0, 0, 0.58, 1.0 };
	static const CubicBezier ease_in_out{ 0.42, 0, 0.58, 1.0 };
};

class UIComponent;

class TranslateTransition : public IAnimation {
	UIComponent* _this;

	int _startX, _startY;
	int _currX, _currY;
	int _targetX, _targetY;
	double _duration;
	
	CubicBezier _easingFunc;
	double _delay;

	bool _loop;

	double _elapsedTime{ 0.0 };
	double _delayTimer{ 0.0 };
	bool _isActive{ false };

public:
	TranslateTransition(
		UIComponent* thisComponent,
		int startX, int startY,
		int targetX, int targetY,
		double duration,
		const CubicBezier& easingFunc,
		double delay = 0.0,
		bool loop = false
	);

	~TranslateTransition() {}

	void Trigger() override {
		_isActive = true;
		_elapsedTime = 0.0;
	}

	void Reset() override {
		_isActive = false;
		_elapsedTime = 0.0;
	}

	bool IsPlaying() override { return _isActive; }

	void Update(double dt) override;

	void Render(Graphics& g) override {}
};

class ColorTransition : public IAnimation {
	using _uchar = unsigned char;

	UIComponent* _this;

	_uchar _startR, _startG, _startB, _startA;
	_uchar _currR, _currG, _currB, _currA;
	_uchar _targetR, _targetG, _targetB, _targetA;
	double _duration;
	
	CubicBezier _easingFunc;
	double _delay;

	bool _loop;

	double _elapsedTime{ 0.0 };
	double _delayTimer{ 0.0 };
	bool _isActive{ false };

public:
	ColorTransition(
		UIComponent* thisComponent,
		std::initializer_list<_uchar> startColor,
		std::initializer_list<_uchar> targetColor,
		double duration,
		const CubicBezier& easingFunc,
		double delay = 0.0,
		bool loop = false
	);

	~ColorTransition() {}

	void Trigger() override {
		_isActive = true;
		_elapsedTime = 0.0;
	}

	void Reset() override {
		_isActive = false;
		_elapsedTime = 0.0;
	}

	bool IsPlaying() override { return _isActive; }

	void Update(double dt) override;

	void Render(Graphics& g) override {}
};

class ImageTransition : public IAnimation {
	using _uchar = unsigned char;

	UIComponent* _this;

	float _startIntensity, _startAlpha;
	float _currIntensity, _currAlpha;
	float _targetIntensity, _targetAlpha;
	double _duration;

	CubicBezier _easingFunc;
	double _delay;

	bool _loop;

	double _elapsedTime{ 0.0 };
	double _delayTimer{ 0.0 };
	bool _isActive{ false };

public:
	ImageTransition(
		UIComponent* thisComponent,
		std::initializer_list<float> startValues,
		std::initializer_list<float> targetValues,
		double duration,
		const CubicBezier& easingFunc,
		double delay = 0.0,
		bool loop = false
	);

	~ImageTransition() {}

	void Trigger() override {
		_isActive = true;
		_elapsedTime = 0.0;
	}

	void Reset() override {
		_isActive = false;
		_elapsedTime = 0.0;
	}

	bool IsPlaying() override { return _isActive; }

	void Update(double dt) override;

	void Render(Graphics& g) override {}

};

class TextAnimation : public IAnimation {
	using _uchar = unsigned char;

	UIComponent* _this;

	std::size_t _numWChars;
	std::size_t _bufIndex{ 0 };
	wchar_t* _buffer;
	std::size_t _typingIndex{ 0 };
	wchar_t* _typingBuffer;
	double _duration;

	double _delay;
	int _typeDelay;
	bool _loop;

	double _typingSpeed{ 0.0 };
	double _elapsedTime{ 0.0 };
	double _delayTimer{ 0.0 };
	bool _isActive{ false };

public:
	TextAnimation(
		UIComponent* thisComponent,
		const wchar_t* text,
		double duration,
		double delay = 0.0,
		bool loop = false
	);

	~TextAnimation() {
		delete[] _buffer;
		delete[] _typingBuffer;
	}

	void Trigger() override {
		_isActive = true;
		_elapsedTime = 0.0;
		_bufIndex = 0;
		_typingIndex = 0;
		std::memset(_typingBuffer, '\0', sizeof(wchar_t) * (_numWChars + 1));
	}

	void Reset() override {
		_isActive = false;
		_elapsedTime = 0.0;
		// Reset Buffer index and typing index
		_bufIndex = 0;
		_typingIndex = 0;
		std::memset(_typingBuffer, '\0', sizeof(wchar_t) * (_numWChars + 1));
	}

	bool IsPlaying() override { return _isActive; }

	void Update(double dt) override;

	void Render(Graphics& g) override {}

};
