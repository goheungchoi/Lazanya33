#pragma once

#include "Animation.h"

class ChainedAnimationPack : public IAnimation {
	std::vector<IAnimation*> _animations;
	int _currentIndex;
	IAnimation* _currentAnimation;

	bool _isTriggered{ false };

	bool _loop{ false };

public:
	ChainedAnimationPack() 
		: IAnimation(0, 0), 
		_currentIndex{ 0 }, 
		_currentAnimation{ nullptr } {}

	void PushBackAnimation(IAnimation* animation) {
		_animations.push_back(animation);
	}

	void PushBackAnimation(std::initializer_list<IAnimation*> ilist) {
		_animations.insert(_animations.end(), ilist);
	}

	void Trigger() override {
		if (_animations.empty()) return;
		_isTriggered = true;
		_currentAnimation = _animations[_currentIndex % _animations.size() ];
		_currentAnimation->Trigger();
	}

	void Reset() override {
		_isTriggered = false;
		_currentIndex = 0;
		_currentAnimation = _animations[_currentIndex];
	}

	bool IsPlaying() override {
		return _isTriggered;
	}

	void SetLoop(bool loop) {
		_loop = loop;
	}

	void Update(double dt) override {
		if (!_isTriggered || !_currentAnimation) return;

		if (!_currentAnimation->IsPlaying()) {
			_isTriggered = false;
		}

		if (_currentIndex == _animations.size()) {
			if (_loop) {
				_currentIndex = 0;
			}
			else {
				Reset();
				return;
			}
		}

		_currentAnimation = _animations[_currentIndex];
		_currentAnimation->Trigger();

		_currentAnimation->Update(dt);

		++_currentIndex;
	}

	void Render(Graphics& g) override {
		if (!_isTriggered || !_currentAnimation) return;

		_currentAnimation->Render(g);
	}
};
