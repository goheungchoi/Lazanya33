#pragma once

#include "Animation.h"

class BlendedAnimationPack : public IAnimation {
	std::vector<IAnimation*> _animations;

	bool _isActive{ false };
	bool _isPlaying{ false };
	bool _isLoop{ false };
public:
	BlendedAnimationPack()
		: IAnimation(0, 0) {}

	void AddAnimation(IAnimation* animation) {
		_animations.push_back(animation);
	}

	void AddAnimation(std::initializer_list<IAnimation*> ilist) {
		_animations.insert(_animations.end(), ilist);
	}

	void SetLoop(bool loop) {
		_isLoop = loop;
	}

	void Trigger() override {
		_isActive = true;
		_isPlaying = true;
		for (IAnimation* animation : _animations) {
			animation->Trigger();
		}
	}

	void Reset() override {
		_isActive = false;
		_isPlaying = false;
	}

	bool IsPlaying() override { return _isActive; }

	void Update(double dt) override {
		if (!_isActive || !_isPlaying) return;

		bool _checkAllStopped = false;
		for (IAnimation* animation : _animations) {
			animation->Update(dt);
			_checkAllStopped |= animation->IsPlaying();
		}

		_isPlaying = _checkAllStopped;
  }

	void Render(Graphics& g) override {
		if (!_isActive || !_isPlaying) return;

		for (IAnimation* animation : _animations) {
			animation->Render(g);
		}
	}
};
