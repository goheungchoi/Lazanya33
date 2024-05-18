#pragma once

#include "IRenderable.h"

class Animation : public IRenderable {
  std::vector<Rect> _frames;  // Frames in the sprite sheet
  Image* _spriteSheet;
  double _frameDuration;
  double _currentFrameTime;
  int _currentFrameIndex;

  bool _isLoop;

public:
  void Update(double dt) {
    _currentFrameTime += dt;
    if (_currentFrameTime >= _frameDuration) {
      _currentFrameTime = (_currentFrameIndex + 1) % _frames.size();
      _currentFrameTime = 0;
    }
  }



	void Render(Graphics& g) override {
		// Render the current frame from the sprite sheet;

		//Image image(L"Apple.gif");
		//UINT width = image.GetWidth();
		//UINT height = image.GetHeight();
		//// Make the destination rectangle 30 percent wider and
		//// 30 percent taller than the original image.
		//// Put the upper-left corner of the destination
		//// rectangle at (150, 20).
		//Rect destinationRect(150, 20, 1.3 * width, 1.3 * height);
		//// Draw the image unaltered with its upper-left corner at (0, 0).
		//graphics.DrawImage(&image, 0, 0);
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
	}
};
