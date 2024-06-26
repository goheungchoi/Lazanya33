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
	IRenderable* _parent{nullptr};
	std::list<IRenderable*> _children;

public:
	IRenderable() : _position{ 0, 0 } {}
	IRenderable(int x, int y) : _position{ x, y } {}
	virtual ~IRenderable() {}

	virtual void SetPosition(int x, int y) {
		_position.X = x;
		_position.Y = y;
	}

	virtual int GetX() {
		return _position.X;
	}

	virtual int GetY() {
		return _position.Y;
	}

	virtual void Render(Graphics& g) = 0;

	virtual void CacheData(Graphics& g) {}

	void AttachChildRenderable(IRenderable* child) {
    child->_parent = this;
		_children.push_back(child);
	}

	void RemoveChildRenderable(IRenderable* child) { 
		child->_parent = nullptr;
		_children.remove(child);
	}

	virtual void RenderChildren(Graphics& g) {
		// Translate the position of children in accordance with 
		// the parent position!
		for (auto pChild : _children) {
			pChild->Render(g);
		}
	}
};

//template<class T>
//concept Renderable = std::is_base_of_v<IRenderable, T>;
