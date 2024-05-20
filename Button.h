#pragma once

#include "UIComponent.h"

class Button : public UIComponent {
	using _uchar = unsigned char;
	using ColorTuple = std::tuple<_uchar, _uchar, _uchar, _uchar>;
  static std::size_t numButtons;  // �׳� ��ư ������� ���� ���� ����

  bool _isPressed{ false };  // ���ȴ��� üũ�ϴ� �Ҹ��� ����
  std::unordered_map<std::string, std::function<void()>> _eventHandlers;  // �̺�Ʈ �ݹ� �Լ� ��� �ؽ� ��

	bool _defaultFill{ true };
	ColorTuple _defaultColor;
	bool _mouseEnterFill{ true };
	ColorTuple _onMouseEnterColor;
	bool _mouseDownFill{ true };
	ColorTuple _onMouseDownColor;
	bool _mouseClickFill{ true };
	ColorTuple _onMouseClickColor;

public:
  Button(int x, int y, int w, int h)
		: Button{ x, y, w, h, L"" } {}

  Button(int x, int y, int w, int h, const wchar_t* text)
    : UIComponent(x, y, w, h),
		_defaultColor{ 180, 180, 180, 255 },
		_onMouseEnterColor{ 220, 220, 220, 255 },
		_onMouseDownColor{ 120, 120, 120, 255 },
		_onMouseClickColor{ 180, 180, 180, 255 }{
    SetText(text);  // Ŀ���� �ؽ�Ʈ

		EnableFill(false);
    SetImageAlpha(255);

    ++numButtons;
  }

  ~Button() {
    --numButtons;
  }

	void EnableButtonDefaultFill(bool enable) {
		_defaultFill = enable;
	}

	void EnableMouseEnterFill(bool enable) {
		_mouseEnterFill = enable;
	}

	void EnableMouseDownFill(bool enable) {
		_mouseDownFill = enable;
	}

	void EnableMouseClickFill(bool enable) {
		_mouseClickFill = enable;
	}

	void SetButtonDefaultColor(char r, char g, char b, char a = 255) {
		_defaultColor = { r, g, b, a };
	}

	void SetMouseEnterColor(char r, char g, char b, char a = 255) {
		_onMouseEnterColor = { r, g, b, a };
	}

	void SetMouseDownColor(char r, char g, char b, char a = 255) {
		_onMouseDownColor = { r, g, b, a };
	}

	void SetMouseClickColor(char r, char g, char b, char a = 255) {
		_onMouseClickColor = { r, g, b, a };
	}

  // ���콺 ��ǥ�� ��ư �ȿ� ���Դ��� �׽�Ʈ�ϴµ� ���̴� �Լ�
  // �� AABB �� ����Ʈ ���ͷ��� �׽�Ʈ
  bool HitTest(int mouseX, int mouseY) {
    return mouseX >= _x && mouseX <= (_x + _width) &&
      mouseY >= _y && mouseY <= (_y + _height);
  }

  // ���� �߿��� �Լ�
  // ��ư Ŭ���� �ٱ����� �Լ� Ŀ���� �̺�Ʈ�� ������ �� �ְ� �ϴ� �Լ���.
  // ���� ���, ���� ���� ������ ���� �÷��� ������ �Ѿ�� �� �̺�Ʈ�� �ɾ��ַ���,
  // Psuedo �ڵ��
  // void ChangeToGamePlay() {
  //   renderSystem.clear();
  //   renderSystem.add(_gamePlayScene);
  // }
  // ��� �Լ��� ����� ����,
  // void Init() {
  //   ...
  //   AddEventLister("mouseClick", &ChangeToGamePlay);
  //   ...
  // }
  // �̷��� �Լ� �����͸� �̺�Ʈ�� �ɾ��ָ�, ���콺 Ŭ�� �� �� �Լ��� ������ ��.
  void AddEventLister(const char* eventName, std::function<void()> callback) {
    _eventHandlers[eventName] = callback;
  }

  void OnMouseEnter() {
    // Change appearance, e.g., highlight
    SetImageAlpha(230);
    _mouseEnterFill && SetFillColor(
			std::get<0>(_onMouseEnterColor), 
			std::get<1>(_onMouseEnterColor),
			std::get<2>(_onMouseEnterColor), 
			std::get<3>(_onMouseEnterColor)
		);
    if (auto it = _eventHandlers.find("mouseEnter");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // ���콺 ��ǥ�� ��ư�� ���
  void OnMouseLeave() {
    // Revert appearance
    SetImageAlpha(255);
    _defaultFill && SetFillColor(
			std::get<0>(_defaultColor), 
			std::get<1>(_defaultColor),
			std::get<2>(_defaultColor), 
			std::get<3>(_defaultColor)
		);
    if (auto it = _eventHandlers.find("mouseLeave");
      it != _eventHandlers.end()) {
      it->second();
    }
    _isPressed = false;
  }

  // ���콺 ��ư �ٿ�
  void OnMouseDown() {
    // Maybe shown as pressed
    _isPressed = true;
    SetImageAlpha(200);
    _mouseDownFill && SetFillColor(
			std::get<0>(_onMouseDownColor), 
			std::get<1>(_onMouseDownColor),
			std::get<2>(_onMouseDownColor), 
			std::get<3>(_onMouseDownColor)
		);
    if (auto it = _eventHandlers.find("mouseDown");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // ���콺 ��ư ��
  void OnMouseUp() {
    // Perform action
    if (_isPressed) {
      SetImageAlpha(255);
			_mouseClickFill && SetFillColor(
				std::get<0>(_onMouseClickColor), 
				std::get<1>(_onMouseClickColor),
				std::get<2>(_onMouseClickColor), 
				std::get<3>(_onMouseClickColor)
			);
      if (_eventHandlers.find("mouseClick") != _eventHandlers.end()) {
        _eventHandlers["mouseClick"]();
      }
			_isPressed = false;
		} else {
			OnMouseEnter();
		}
  }

  // Ȥ�� ���� ����� ���� ������ �������̵� �Լ�
  virtual void Render(Graphics& g) override {
    UIComponent::Render(g);

    // Ȥ�� ������ �� �� �� ������ �߰�.
    // ������ ���ص� ��.

  }
};

inline std::size_t Button::numButtons{ 0 };

// ��ư ������ �ؿ� �ִ°� ���� �ý����̳� �ڵ鷯�� �ʿ���.
// �ؿ� �ִ°� ����. �״�� �����ٰ� ���Ϸ� �и��ؼ� �ᵵ ��� ����.
// ��ư �̺�Ʈ �ڵ鷯�� ���� �ϳ��� ��� �ְ�,
// ����: �� ������ ������Ʈ ���� ���콺 X, Y ��ǥ�� Ŭ���Ǿ������� ���� ������ �޾Ƽ�
// ���� ��ư���� �̺�Ʈ�� Ȯ��, ������.
class ButtonEventHandler {
  std::vector<Button*> buttons;  // This holds all buttons in the UI

public:
  ButtonEventHandler() {}

  void AddButton(Button* button) {
    buttons.push_back(button);
  }

  void HandleMouseEvent(int mouseX, int mouseY, bool isDown, bool isUp) {
    for (auto* button : buttons) {
      if (button->HitTest(mouseX, mouseY)) {
        if (isDown) {
          button->OnMouseDown();
				} else if (isUp) {
					button->OnMouseUp();
				}
      } else {
        button->OnMouseLeave();
      }
    }
  }
};