#pragma once

using namespace Gdiplus;

enum class H_DIRECTION {
  LEFT = 0b0001,
  RIGHT = 0b0010,
  CENTER = 0b0011,
};

enum class V_DIRECTION { 
  TOP = 0b0100, 
  CENTER = 0b1100, 
  BOTTOM = 0b1000 
};

class IRenderable {
protected:
	Point _position;
	std::vector<IRenderable*> _children;

public:
	IRenderable() : _position{ 0, 0 }, _children(5, nullptr) {}
	IRenderable(int x, int y) : _position{ x, y }, _children(5, nullptr) {}
	virtual ~IRenderable() {}

	void SetPosition(int x, int y) {
		_position.X = x;
		_position.Y = y;
	}

	virtual void Render(Graphics& g) = 0;

	virtual void CacheData(Graphics& g) {}

	void AttachChildRenderable(IRenderable* child) {
		_children.push_back(child);
	}

	virtual void RenderChildren(Graphics& g) {
		// Translate the position of children in accordance with 
		// the parent position!
		for (auto pChild : _children) {
			pChild->Render(g);
		}
	}
};
