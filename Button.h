#pragma once

#include "UIComponent.h"

class Button : public UIComponent {
	static std::size_t numButtons;

	bool _isPressed{ false };
	std::unordered_map<std::string, std::function<void()>> _eventHandlers;

public:
	Button(int x, int y, int w, int h)
	: UIComponent(x, y, w, h) {
		wchar_t buf[25];
		swprintf_s(buf, L"Button%llu", numButtons);
		SetText(buf);
		EnableBorder(true);
		SetBorder(0, 0, 0);
		EnableFill(true);
		SetFillColor(180, 180, 180);

		++numButtons;
	}

	Button(int x, int y, int w, int h, const wchar_t* text)
	: UIComponent(x, y, w, h) {
		SetText(text);
		EnableBorder(true);
		SetBorder(0, 0, 0);
		EnableFill(true);
		SetFillColor(180, 180, 180);

		++numButtons;
	}

	~Button() {
		--numButtons;
	}

	bool HitTest(int mouseX, int mouseY) {
    return mouseX >= _x && mouseX <= (_x + _width) &&
			mouseY >= _y && mouseY <= (_y + _height);
  }

	void AddEventLister(const char* eventName, std::function<void()> callback) {
		_eventHandlers[eventName] = callback;
	}

	void OnMouseEnter() {
		// Change appearance, e.g., highlight
		SetFillColor(220, 220, 220); 
		if (auto it = _eventHandlers.find("mouseEnter"); 
			it != _eventHandlers.end()) {
			it->second();
    }
  }

  void OnMouseLeave() {
		// Revert appearance
		SetFillColor(180, 180, 180); 
		if (auto it = _eventHandlers.find("mouseLeave"); 
			it != _eventHandlers.end()) {
			it->second();
    }
  }

  void OnMouseDown() {
		// Maybe show as pressed
		_isPressed = true;
		SetFillColor(120, 120, 120); // Make it darker
		if (auto it = _eventHandlers.find("mouseDown"); 
			it != _eventHandlers.end()) {
			it->second();
    }
  }

  void OnMouseUp() {
		// Perform action
		if (_isPressed) {
      if (_eventHandlers.find("mouseClick") != _eventHandlers.end()) {
        _eventHandlers["mouseClick"]();
      }
    }
		_isPressed = false;
  }

	virtual void Render(Graphics& g) override {
		UIComponent::Render(g);


	}
};

std::size_t Button::numButtons{ 0 };


// Example
class ButtonEventHandler {
	std::vector<Button*> buttons;  // This holds all buttons in the UI

public:
	ButtonEventHandler() {}

	void AddButton(Button* button) {
		buttons.push_back(button);
	}

  void HandleMouseEvent(int mouseX, int mouseY, bool isClick) {
    for (auto* button : buttons) {
      if (button->HitTest(mouseX, mouseY)) {
        if (isClick) {
          button->OnMouseDown();
        } else {
					button->OnMouseEnter();
        }
      } else {
        button->OnMouseLeave();
      }
    }
  }
};
