#pragma once

#include "Animation.h"

class AnimationController {
public:
  void AddAnimation(int state, Animation* animation) {
    _animations[state] = animation;
  }

  void SetState(int newState) {
    auto it = _animations.find(newState);
    if (it != _animations.end()) {
      _currentAnimation = it->second;
    }
  }

  void Update(float deltaTime) {
    if (_currentAnimation) {
      _currentAnimation->Update(deltaTime);
    }
  }

  IRenderable* GetCurrentFrame() const {
    return _currentAnimation;
  }

 private:
  std::unordered_map<int, Animation*> _animations;
  Animation* _currentAnimation;
};
