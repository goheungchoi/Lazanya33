#pragma once

#include "Animation.h"

using namespace Gdiplus;

class AnimationController {
  std::unordered_map<int, IAnimation*> _animations;
	IAnimation* _currentAnimation{ nullptr };

public:
  void AddAnimation(int state, IAnimation* animation) {
    _animations[state] = animation;
  }

  void SetState(int newState) {
    auto it = _animations.find(newState);
		
    if (it != _animations.end()) {
			if (it->second == _currentAnimation &&
				_currentAnimation->IsPlaying()
			) return;
      _currentAnimation = it->second;
			_currentAnimation->Trigger();
		}
		else {
			Reset();
		}
  }

	void Reset() {
		for (auto p : _animations) {
			p.second->Reset();
		}
		_currentAnimation = nullptr;
	}

  void Update(double deltaTime) {
		if (!_currentAnimation) return;
    _currentAnimation->Update(deltaTime);
  }

  IRenderable* GetCurrentAnimation() const {
    return _currentAnimation;
  }

	void Render(Graphics& g) {
		if (!_currentAnimation) return;
		_currentAnimation->Render(g);
	}
};
