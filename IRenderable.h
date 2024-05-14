#pragma once

using namespace Gdiplus;

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

	virtual void Render(Gdiplus::Graphics& g) = 0;

	void AttachChildRenderable(IRenderable* child) {
		_children.push_back(child);
	}
	virtual void RenderChildren(Gdiplus::Graphics& g) {
		// Translate the position of children in accordance with 
		// the parent position!
		for (auto pChild : _children) {
			pChild->Render(g);
		}
	}
};
