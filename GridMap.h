#pragma once

#include "CollectiveRenderable.h"

template<class T>
class GridItem : public MultiSpriteRenderable<T> {
	Point _gridPos;

public:
		

};

class GridMap : public MultiSpriteRenderable<GridMap> {
	std::size_t _cellWidth;
	std::size_t _cellHeight;

public: 
	GridMap(int x, int y, 
	std::size_t nrows, std::size_t ncols, 
	std::size_t cellWidth, std::size_t cellHeight)
	: _cellWidth{cellWidth}, _cellHeight{cellHeight},
		MultiSpriteRenderable<GridMap>(x, y, cellWidth*nrows, cellHeight*ncols) {}

	void Render(Graphics& g) override { 
		MultiSpriteRenderable<GridMap>::Render(g);
		RenderChildren(g); 
	}

	void RenderChildren(Graphics& g) override {
		g.TranslateTransform(_position.X, _position.Y);
		g.ScaleTransform(_cellWidth, _cellHeight);
		for (auto& pChild : _children) { 
			pChild->Render(g);
		}
		g.ResetTransform();
    //g.ResetTransform();
	}
};
