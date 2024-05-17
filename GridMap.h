#pragma once

#include "UIComponent.h"

#include "GridItem.h"

class GridMap : public UIComponent {
	std::list<GridItem*> _gridItems;

public:
	
	void AddGridItem(GridItem* item) {
		_gridItems.push_back(item);
	}

	void RemoveGridItem(GridItem* item) {
		_gridItems.remove(item);
	}

private:
	std::size_t _cellWidth;
	std::size_t _cellHeight;

public: 
	GridMap(int x, int y, 
	std::size_t nrows, std::size_t ncols, 
	std::size_t cellWidth, std::size_t cellHeight)
	: _cellWidth{cellWidth}, _cellHeight{cellHeight},
		UIComponent(x, y, cellWidth*nrows, cellHeight*ncols) {}

	void Render(Graphics& g) override { 
		UIComponent::Render(g);
		RenderChildren(g); 
	}

	void RenderChildren(Graphics& g) override {
		/*g.TranslateTransform(_position.X, _position.Y);
		g.ScaleTransform(_cellWidth, _cellHeight);*/


		for (GridItem* pGridItem : _gridItems) { 
			pGridItem->Render(g);
		}


		//g.ResetTransform();
    //g.ResetTransform();
	}
};
