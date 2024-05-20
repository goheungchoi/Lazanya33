#pragma once

#include "UIComponent.h"

class Button : public UIComponent {
	using _uchar = unsigned char;
	using ColorTuple = std::tuple<_uchar, _uchar, _uchar, _uchar>;
  static std::size_t numButtons;  // 그냥 버튼 만들어진 개수 세는 변수

  bool _isPressed{ false };  // 눌렸는지 체크하는 불리안 변수
  std::unordered_map<std::string, std::function<void()>> _eventHandlers;  // 이벤트 콜백 함수 담는 해쉬 맵

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
    SetText(text);  // 커스텀 텍스트

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

  // 마우스 좌표가 버튼 안에 들어왔는지 테스트하는데 쓰이는 함수
  // 걍 AABB 랑 포인트 인터렉션 테스트
  bool HitTest(int mouseX, int mouseY) {
    return mouseX >= _x && mouseX <= (_x + _width) &&
      mouseY >= _y && mouseY <= (_y + _height);
  }

  // 제일 중요한 함수
  // 버튼 클래스 바깥에서 함수 커스텀 이벤트를 설정할 수 있게 하는 함수임.
  // 예를 들면, 게임 레터 씬에서 게임 플레이 씬으로 넘어가는 걸 이벤트로 걸어주려면,
  // Psuedo 코드로
  // void ChangeToGamePlay() {
  //   renderSystem.clear();
  //   renderSystem.add(_gamePlayScene);
  // }
  // 라는 함수를 만들고 나서,
  // void Init() {
  //   ...
  //   AddEventLister("mouseClick", &ChangeToGamePlay);
  //   ...
  // }
  // 이렇게 함수 포인터를 이벤트에 걸어주면, 마우스 클릭 때 이 함수가 실행이 됨.
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

  // 마우스 좌표가 버튼을 벗어남
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

  // 마우스 버튼 다운
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

  // 마우스 버튼 업
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

  // 혹시 몰라서 만들어 놓은 렌더링 오버라이딩 함수
  virtual void Render(Graphics& g) override {
    UIComponent::Render(g);

    // 혹시 렌더링 더 할 거 있으면 추가.
    // 없으면 안해도 됨.

  }
};

inline std::size_t Button::numButtons{ 0 };

// 버튼 쓰려면 밑에 있는거 같은 시스템이나 핸들러가 필요함.
// 밑에 있는건 예시. 그대로 가져다가 파일로 분리해서 써도 상관 없음.
// 버튼 이벤트 핸들러는 씬이 하나씩 들고 있고,
// 목적: 매 프레임 업데이트 마다 마우스 X, Y 좌표랑 클릭되었는지에 대한 정보를 받아서
// 각각 버튼마다 이벤트를 확인, 실행함.
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