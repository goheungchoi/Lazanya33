#pragma once

#include "UIComponent.h"

class Button : public UIComponent {
  static std::size_t numButtons;  // 그냥 버튼 만들어진 개수 세는 변수

  bool _isPressed{ false };  // 눌렸는지 체크하는 불리안 변수
  std::unordered_map<std::string, std::function<void()>> _eventHandlers;  // 이벤트 콜백 함수 담는 해쉬 맵

public:
  Button(int x, int y, int w, int h)
    : UIComponent(x, y, w, h) {
    // Default Construct 는 함수 텍스트에 "Button{numButtons}" 이라고 프린팅
    wchar_t buf[25];
    swprintf_s(buf, L"Button%llu", numButtons);
    SetText(buf);
    // 보더 검은색
    EnableBorder(true);
    SetBorder(0, 0, 0);
    // 채우기 약간 회색
    EnableFill(true); // <- 색 테스트용. 지워도 됨
    SetFillColor(180, 180, 180); // <- 색 테스트용. 지워도 됨

    ++numButtons;
  }

  Button(int x, int y, int w, int h, const wchar_t* text)
    : UIComponent(x, y, w, h) {
    SetText(text);  // 커스텀 텍스트
    // 보더 검은색
    EnableBorder(true);
    SetBorder(0, 0, 0);
    // 채우기 약간 회색
    EnableFill(true); // <- 색 테스트용. 지워도 됨
    SetFillColor(180, 180, 180); // <- 색 테스트용. 지워도 됨
    ++numButtons;
  }

  ~Button() {
    --numButtons;
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
    SetFillColor(220, 220, 220); // <- 색 테스트용. 지워도 됨
    if (auto it = _eventHandlers.find("mouseEnter");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // 마우스 좌표가 버튼을 벗어남
  void OnMouseLeave() {
    // Revert appearance
    SetFillColor(180, 180, 180); // <- 색 테스트용. 지워도 됨
    if (auto it = _eventHandlers.find("mouseLeave");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // 마우스 버튼 다운
  void OnMouseDown() {
    // Maybe shown as pressed
    _isPressed = true;
    SetFillColor(120, 120, 120); // <- 색 테스트용. 지워도 됨
    if (auto it = _eventHandlers.find("mouseDown");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // 마우스 버튼 업
  void OnMouseUp() {
    // Perform action
    if (_isPressed) {
      if (_eventHandlers.find("mouseClick") != _eventHandlers.end()) {
        _eventHandlers["mouseClick"]();
      }
    }
    _isPressed = false;
  }

  // 혹시 몰라서 만들어 놓은 렌더링 오버라이딩 함수
  virtual void Render(Graphics& g) override {
    UIComponent::Render(g);

    // 혹시 렌더링 더 할 거 있으면 추가.
    // 없으면 안해도 됨.

  }
};

std::size_t Button::numButtons{ 0 };

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

  void HandleMouseEvent(int mouseX, int mouseY, bool isClick) {
    for (auto* button : buttons) {
      if (button->HitTest(mouseX, mouseY)) {
        if (isClick) {
          button->OnMouseDown();
        }
        else {
          button->OnMouseEnter();
        }
      }
      else {
        button->OnMouseLeave();
      }
    }
  }
};