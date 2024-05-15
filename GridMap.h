#pragma once

#include "IRenderable.h"

template<
std::size_t nrows, 
std::size_t ncols,
std::size_t width,
std::size_t height
>
class GridMap : public IRenderable {
	std::size_t _cellWidth;
	std::size_t _cellHeight;
	
	Matrix _T;

public:
	constexpr 
	GridMap(int x, int y)
	: _cellWidth{width / nrows}, _cellHeight{height / ncols},
		IRenderable(x, y) {}

	void RenderChildren(Graphics& g) override {
		


	}
};
