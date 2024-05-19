#include "Animation.h"

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

