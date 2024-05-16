#pragma once

#include "IRenderable.h"

// TODO: Need to handle some player interaction (button - mouse hover)
// TODO: Might need some loop animations

// UIComponent can inherit from either SingleRenderable or CollectiveRenderable

class UIComponent : public IRenderable {
	




	// Change appearance, e.g., highlight
	virtual void OnMouseEnter() = 0;

	// Revert appearance
  virtual void OnMouseLeave() = 0;

	// Maybe show as pressed
  virtual void OnMouseDown() = 0;

	// Perform action
  virtual void OnMouseUp() = 0;


	virtual void Render() {
		

	}

};

