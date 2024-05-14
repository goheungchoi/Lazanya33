#pragma once

#include "IRenderable.h"

class Animation : public IRenderable {
  std::vector<Rect> _frames;  // Frames in the sprite sheet
  Image* _spriteSheet;
  float _frameDuration;
  float _currentFrameTime;
  int _currentFrameIndex;

  bool _isLoop;

public:
  void Update(float dt) {
    _currentFrameTime += dt;
    if (_currentFrameTime >= _frameDuration) {
      _currentFrameTime = (_currentFrameIndex + 1) % _frames.size();
      _currentFrameTime = 0;
    }
  }

  void Render(Graphics& g) override {
    // Render the current frame from the sprite sheet;
  }
};
