#pragma once

#include "UIComponent.h"
#include "Div.h"

template<
std::size_t nrows, 
std::size_t ncols,
std::size_t width,
std::size_t height
>
class GridMap : public Div<CollectiveRenderable<GridMap>> {
	std::size_t _cellWidth;
	std::size_t _cellHeight;
	Matrix _T;

public: 
	GridMap(int x, int y)
	: _cellWidth{width / nrows}, _cellHeight{height / ncols},
		IRenderable(x, y) {
		T.Scale(_cellWidth, _cellHeight);
		T.TransformPoints(_position.X, _position.Y);
	}

	void Render(Graphics& g) override { 
		CollectiveRenderable<GridMap>::Render(g);
		RenderChildren(g); 
	}

	void RenderChildren(Graphics& g) override {
		g.SetTransform(&_T);
		for (auto& pChild : _children) { 
			pChild->Render(g);
		}
    g.ResetTransform();
	}
};
