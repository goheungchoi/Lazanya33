#pragma once

#include "UIComponent.h"

class Button : public UIComponent {
  static std::size_t numButtons;  // �׳� ��ư ������� ���� ���� ����

  bool _isPressed{ false };  // ���ȴ��� üũ�ϴ� �Ҹ��� ����
  std::unordered_map<std::string, std::function<void()>> _eventHandlers;  // �̺�Ʈ �ݹ� �Լ� ��� �ؽ� ��

public:
  Button(int x, int y, int w, int h)
    : UIComponent(x, y, w, h) {
    // Default Construct �� �Լ� �ؽ�Ʈ�� "Button{numButtons}" �̶�� ������
    wchar_t buf[25];
    swprintf_s(buf, L"Button%llu", numButtons);
    SetText(buf);
    // ���� ������
    EnableBorder(true);
    SetBorder(0, 0, 0);
    // ä��� �ణ ȸ��
    EnableFill(true); // <- �� �׽�Ʈ��. ������ ��
    SetFillColor(180, 180, 180); // <- �� �׽�Ʈ��. ������ ��

    ++numButtons;
  }

  Button(int x, int y, int w, int h, const wchar_t* text)
    : UIComponent(x, y, w, h) {
    SetText(text);  // Ŀ���� �ؽ�Ʈ
    // ���� ������
    EnableBorder(true);
    SetBorder(0, 0, 0);
    // ä��� �ణ ȸ��
    EnableFill(true); // <- �� �׽�Ʈ��. ������ ��
    SetFillColor(180, 180, 180); // <- �� �׽�Ʈ��. ������ ��
    ++numButtons;
  }

  ~Button() {
    --numButtons;
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
    SetFillColor(220, 220, 220); // <- �� �׽�Ʈ��. ������ ��
    if (auto it = _eventHandlers.find("mouseEnter");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // ���콺 ��ǥ�� ��ư�� ���
  void OnMouseLeave() {
    // Revert appearance
    SetFillColor(180, 180, 180); // <- �� �׽�Ʈ��. ������ ��
    if (auto it = _eventHandlers.find("mouseLeave");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // ���콺 ��ư �ٿ�
  void OnMouseDown() {
    // Maybe shown as pressed
    _isPressed = true;
    SetFillColor(120, 120, 120); // <- �� �׽�Ʈ��. ������ ��
    if (auto it = _eventHandlers.find("mouseDown");
      it != _eventHandlers.end()) {
      it->second();
    }
  }

  // ���콺 ��ư ��
  void OnMouseUp() {
    // Perform action
    if (_isPressed) {
      if (_eventHandlers.find("mouseClick") != _eventHandlers.end()) {
        _eventHandlers["mouseClick"]();
      }
    }
    _isPressed = false;
  }

  // Ȥ�� ���� ����� ���� ������ �������̵� �Լ�
  virtual void Render(Graphics& g) override {
    UIComponent::Render(g);

    // Ȥ�� ������ �� �� �� ������ �߰�.
    // ������ ���ص� ��.

  }
};

std::size_t Button::numButtons{ 0 };

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