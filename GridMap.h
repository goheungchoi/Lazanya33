#pragma once

#include "IRenderable.h"

template<std::size_t nrows, std::size_t ncols>
class GridMap : public IRenderable {
	std::size_t _cellWidth;
	std::size_t _cellHeight;
	
	Matrix _T;

public:
	constexpr 
	GridMap(std::size_t width, std::size_t height)
	: _cellWidth{width / nrows}, _cellHeight{height / ncols} {}


	void RenderChildren(Graphics& g) {
		
	}

};
