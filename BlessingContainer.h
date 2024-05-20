#pragma once

#include "Container.h"

#include "ResourceManager.h"

using namespace Gdiplus;

enum class BlessingType {
	Anaerobic,
	GoldSeeker,
	Naughty,
	Pummeler,
	SugarGirl,
	TenaciousDwarf,
	Wimp
};

class BlessingContainer : public Container {
	bool _isSelected{ false };
	bool _isPressed{ false };  // ���ȴ��� üũ�ϴ� �Ҹ��� ����
  std::unordered_map<std::string, std::function<void()>> _eventHandlers;  // �̺�Ʈ �ݹ� �Լ� ��� �ؽ� ��

	BlessingType _blessingType;
	Bitmap* _default;
	Bitmap* _selected;
public:
	BlessingContainer(BlessingType blessingType)
		: _blessingType{ blessingType } {
		InitImages(blessingType);
	}

	// Change appearance, e.g., highlight
	void OnMouseEnter() override {
		if (auto it = _eventHandlers.find("mouseEnter");
      it != _eventHandlers.end()) {
      it->second();
    }
	};

	// Revert appearance
  void OnMouseLeave() override {
		if (auto it = _eventHandlers.find("mouseLeave");
      it != _eventHandlers.end()) {
      it->second();
    }
	};

	// Maybe show as pressed
  void OnMouseDown() override {
		if (auto it = _eventHandlers.find("mouseDown");
      it != _eventHandlers.end()) {
      it->second();
    }
	};

	// Perform action
  void OnMouseUp() override {
		// Perform action
    if (_isPressed) {
      if (_eventHandlers.find("mouseClick") != _eventHandlers.end()) {
        _eventHandlers["mouseClick"]();
      }
			_isPressed = false;
		} else {
			OnMouseEnter();
		}
	};

private:

	void InitImages(BlessingType blessingType) {
		switch (blessingType)
		{
		case BlessingType::Anaerobic: {
			_default = ResourceManager::Get().GetImage(L"anaerobic");
			_selected = ResourceManager::Get().GetImage(L"anaerobic_selected");
		} break;
		case BlessingType::GoldSeeker: {
			_default = ResourceManager::Get().GetImage(L"gold_seeker");
			_selected = ResourceManager::Get().GetImage(L"gold_seeker_selected");
		} break;
		case BlessingType::Naughty: {
			_default = ResourceManager::Get().GetImage(L"naughty");
			_selected = ResourceManager::Get().GetImage(L"naughty_selected");
		} break;
		case BlessingType::Pummeler: {
			_default = ResourceManager::Get().GetImage(L"pummeler");
			_selected = ResourceManager::Get().GetImage(L"pummeler_selected");
		} break;
		case BlessingType::SugarGirl: {
			_default = ResourceManager::Get().GetImage(L"sugar_girl");
			_selected = ResourceManager::Get().GetImage(L"sugar_girl_selected");
		} break;
		case BlessingType::TenaciousDwarf: {
			_default = ResourceManager::Get().GetImage(L"tenacious_dwarf");
			_selected = ResourceManager::Get().GetImage(L"tenacious_dwarf_selected");
		} break;
		case BlessingType::Wimp: {
			_default = ResourceManager::Get().GetImage(L"wimp");
			_selected = ResourceManager::Get().GetImage(L"wimp_selected");
		} break;
		default: {
			_default = ResourceManager::Get().GetImage(L"lazanya");
			_selected = ResourceManager::Get().GetImage(L"lazanya_selected");
		} break;
		}
	}
};
