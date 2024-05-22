#pragma once

#include "Animation.h"

class SequentialAnimationPack : public IAnimation {
	std::vector<IAnimation*> _animations;
	int _currentIndex;
	IAnimation* _currentAnimation;

	bool _isTriggered{ false };

	bool _loop{ false };
	std::pair<int, int> _loopRange;

public:
	SequentialAnimationPack() 
		: IAnimation(0, 0), 
		_currentIndex{ 0 }, 
		_currentAnimation{ nullptr },
		_loopRange{ 0, 0 } {}

	void PushBackAnimation(IAnimation* animation) {
		_animations.push_back(animation);
	}

	void PushBackAnimation(std::initializer_list<IAnimation*> ilist) {
		_animations.insert(_animations.end(), ilist);
	}

	void Trigger() override {
		if (_animations.empty()) return;
		_isTriggered = true;
		_currentIndex = 0;
		_currentAnimation = _animations[_currentIndex];
		_currentAnimation->Trigger();
	}

	void Reset() override {
		for (auto* anim : _animations) {
			anim->Reset();
		}

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

	void SetLoopRange(int inclusiveFirst, int exclusiveLast) {
		_loopRange = { inclusiveFirst, exclusiveLast };
	}

	void Update(double dt) override {
		if (!_isTriggered || !_currentAnimation) return;

		if (!_currentAnimation->IsPlaying()) {
			++_currentIndex;

			if (_loop && _currentIndex == _loopRange.second) {
				_currentIndex = _loopRange.first;
			}

			if (_currentIndex == _animations.size()) {
				Reset();
				return;
			}

			_currentAnimation = _animations[_currentIndex];
			_currentAnimation->Trigger();
		}

		_currentAnimation->Update(dt);
	}

	void Render(Graphics& g) override {
		if (!_isTriggered || !_currentAnimation) return;

		_currentAnimation->Render(g);
	}
};
