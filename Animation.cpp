#include "Animation.h"
#include "CSound.h"
#include "UIComponent.h"

TranslateTransition::TranslateTransition(
	UIComponent* thisComponent,
	int startX, int startY,
	int targetX, int targetY,
	double duration,
	const CubicBezier& easingFunc, 
	double delay,
	bool loop
) : IAnimation(targetX, targetY), 
	_this{ thisComponent },
	_startX{startX}, _startY{startY},
	_currX{_startX}, _currY{_startY},
	_targetX{ targetX }, _targetY{ targetY },
	_duration{duration}, _easingFunc{ easingFunc },
	_delay{ delay }, _loop{ loop } {}

void TranslateTransition::Update(double dt) {
	if (!_isActive) return;

	_delayTimer += dt;
	if (_delayTimer < _delay) return;
	_delayTimer = _delay + 1.0;

	_elapsedTime += dt;

	if (_elapsedTime >= _duration) {
		_elapsedTime -= _duration;

		if (_loop) {
			double tmpX = _targetX;
			_targetX = _startX;
			_startX = tmpX;
			double tmpY = _targetY;
			_targetY = _startY;
			_startY = tmpY;
		} else {
			_isActive = false;
		}
	} else {
		double normalizedTime = _elapsedTime / _duration;
		_currX = _startX + (_targetX - _startX) * _easingFunc(normalizedTime);
		_currY = _startY + (_targetY - _startY) * _easingFunc(normalizedTime);
		_this->SetPosition(_currX, _currY);
	}
}

ColorTransition::ColorTransition(
	UIComponent* thisComponent, 
	std::initializer_list<_uchar> startColor, 
	std::initializer_list<_uchar> targetColor,
	double duration, 
	const CubicBezier& easingFunc, 
	double delay, 
	bool loop
) : IAnimation(0, 0), 
	_this{ thisComponent },
	_startR{std::data(startColor)[0]}, 
	_startG{std::data(startColor)[1]}, 
	_startB{std::data(startColor)[2]}, 
	_startA{std::data(startColor)[3]},
	_currR{_startR}, _currG{_startG}, _currB{_startB}, _currA{_startA},
	_targetR{std::data(targetColor)[0]}, 
	_targetG{std::data(targetColor)[1]}, 
	_targetB{std::data(targetColor)[2]}, 
	_targetA{std::data(targetColor)[3]},
	_duration{duration}, _easingFunc{ easingFunc },
	_delay{ delay }, _loop{ loop } {}

void ColorTransition::Update(double dt) {
	if (!_isActive) return;

	_delayTimer += dt;
	if (_delayTimer < _delay) return;
	_delayTimer = _delay + 1.0;

	_elapsedTime += dt;

	if (_elapsedTime >= _duration) {
		_elapsedTime -= _duration;

		if (_loop) {
			_uchar tmpR = _startR;
			_targetR = _startR;
			_startR = tmpR;
			_uchar tmpG = _targetG;
			_targetG = _startG;
			_startG = tmpG;
			_uchar tmpB = _targetB;
			_targetB = _startB;
			_startB = tmpB;
			_uchar tmpA = _targetA;
			_targetA = _startA;
			_startA = tmpA;
		} else {
			_isActive = false;
		}
	} else {
		double normalizedTime = _elapsedTime / _duration;
		_currR = _startR + (_targetR - _startR) * _easingFunc(normalizedTime);
		_currG = _startG + (_targetG - _startG) * _easingFunc(normalizedTime);
		_currB = _startB + (_targetB - _startB) * _easingFunc(normalizedTime);
		_currA = _startA + (_targetA - _startA) * _easingFunc(normalizedTime);
		_this->SetFillColor(_currR, _currG, _currB, _currA);
	}
}

ImageTransition::ImageTransition(
	UIComponent* thisComponent,
	std::initializer_list<float> startValues,
	std::initializer_list<float> targetValues,
	double duration,
	const CubicBezier& easingFunc,
	double delay,
	bool loop
) : IAnimation(0, 0), 
	_this{ thisComponent },
	_startIntensity{std::data(startValues)[0]}, 
	_startAlpha{std::data(startValues)[1]}, 
	_currIntensity{_startIntensity}, _currAlpha{_startAlpha},
	_targetIntensity{std::data(targetValues)[0]}, 
	_targetAlpha{std::data(targetValues)[1]}, 
	_duration{duration}, _easingFunc{ easingFunc },
	_delay{ delay }, _loop{ loop } {}

void ImageTransition::Update(double dt) {
	if (!_isActive) return;

	_delayTimer += dt;
	if (_delayTimer < _delay) return;
	_delayTimer = _delay + 1.0;

	_elapsedTime += dt;

	if (_elapsedTime >= _duration) {
		_elapsedTime -= _duration;

		if (_loop) {
			float tmpIntensity = _startIntensity;
			_targetIntensity = _startIntensity;
			_startIntensity = tmpIntensity;
			float tmpAlpha = _targetAlpha;
			_targetAlpha = _startAlpha;
			_startAlpha = tmpAlpha;
		} else {
			_isActive = false;
		}
	} else {
		double normalizedTime = _elapsedTime / _duration;
		_currIntensity = _startIntensity + (_targetIntensity - _startIntensity) * _easingFunc(normalizedTime);
		_currAlpha = _startAlpha + (_targetAlpha - _startAlpha) * _easingFunc(normalizedTime);
		_this->SetImageIntensity(_currIntensity);
		_this->SetImageAlpha(255 * _currAlpha);
	}
}

TextAnimation::TextAnimation(
	UIComponent* thisComponent,
	const wchar_t* text,
	double duration,
	double delay,
	bool loop
) : IAnimation(0, 0),
	_this{ thisComponent },
	_numWChars{0},
	_duration{ duration },
	_delay{ delay },
	_loop{ loop } {
	while (text[_numWChars++] != '\0') {}
	_buffer = new wchar_t[_numWChars+1];
	_typingBuffer = new wchar_t[_numWChars+1];
	wcsncpy_s(_buffer, _numWChars+1, text, _numWChars + 1);
	(_buffer, text, _numWChars+1);
	std::memset(_typingBuffer, '\0', sizeof(wchar_t) * (_numWChars + 1));
	_typingSpeed = duration / _numWChars;
}

void TextAnimation::Update(double dt) {
	if (!_isActive) return;

	_elapsedTime += dt;
	if (_elapsedTime >= _typingSpeed) {
		_elapsedTime -= _typingSpeed;

		wchar_t nextc = _buffer[_bufIndex];
		
		if (nextc == L'-') {
			_typingSpeed *= 0.5;
		}
		else if (nextc == L'+') {
			_typingSpeed *= 2.0;
		}
		else {
			_typingBuffer[_typingIndex++] = nextc;
			_this->SetText(_typingBuffer);
			if (_typeDelay % 9 == 0)
				Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type1);
			
			else if(_typeDelay %9==3)
				Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type3);
	
			else if (_typeDelay % 9 == 6)
				Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type5);
			_typeDelay++;
		}

		++_bufIndex;

		if (_bufIndex == _numWChars) {
			_isActive = false;
			_typeDelay = 0;
		}
	}
}