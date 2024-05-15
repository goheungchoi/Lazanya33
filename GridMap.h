#pragma once

#include "CollectiveRenderable.h"

class GridMap : public CollectiveRenderable<GridMap> {
	std::size_t _cellWidth;
	std::size_t _cellHeight;
	Matrix _T;

public: 
	GridMap(int x, int y, 
	std::size_t nrows, std::size_t ncols, 
	std::size_t cellWidth, std::size_t cellHeight)
	: _cellWidth{cellWidth}, _cellHeight{cellHeight},
		CollectiveRenderable<GridMap>(x, y) {
		_T.Scale(_cellWidth, _cellHeight);
		_T.Translate(_position.X, _position.Y);
	}

	void Render(Graphics& g) override { 
		CollectiveRenderable<GridMap>::Render(g);
		RenderChildren(g); 
	}

	void RenderChildren(Graphics& g) override {
		//g.SetTransform(&_T);
		for (auto& pChild : _children) { 
			pChild->Render(g);
		}
    //g.ResetTransform();
	}
};
