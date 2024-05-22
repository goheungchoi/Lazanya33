#pragma once

#include "Container.h"

#include "Animation.h"

#include "ResourceManager.h"
#include "RandomGenerator.h"

#include "DebugConsole.h"

using namespace Gdiplus;

enum class BlessingType {
	Virago,
	Anaerobic,
	GoldSeeker,
	Naughty,
	Pummeler,
	SugarGirl,
	TenaciousDwarf,
	Wimp,
	LENGTH
};

constexpr std::size_t BLESSING_TYPE_NUM = static_cast<std::size_t>(BlessingType::LENGTH);

class BlessingsOfGodStateController;

class BlessingContainer : public Container {
	friend class BlessingsOfGodStateController;
	static int count;
	static bool check[BLESSING_TYPE_NUM];

	bool _isPressed{ false };  // 눌렸는지 체크하는 불리안 변수
  std::unordered_map<std::string, std::function<void()>> _eventHandlers;  // 이벤트 콜백 함수 담는 해쉬 맵

	BlessingType _blessingType;
	Bitmap* _default;
	Bitmap* _selected;

	bool _isDarker{ false };
	ImageTransition _darkenImageTransition;
	ImageTransition _brightenImageTransition;

public:
	BlessingContainer(int x, int y, int w, int h)
		: Container(x, y, w, h),
		_darkenImageTransition(
			this, 
			{1.0, 1.0}, 
			{0.3, 1.0},
			0.5, bezier::ease_in_out), 
		_brightenImageTransition(
			this, 
			{0.3, 1.0}, 
			{1.0, 1.0},
			0.5, bezier::ease_in_out) {
		if (count == 0) {
			check[0] = true;
			_blessingType = BlessingType::Virago;
		}
		else {
			int i = 0;
			while (check[i]) {	// Make sure there are no duplicate types.
				i = RandomGenerator::Get<int>(BLESSING_TYPE_NUM - 1);
			}
			check[i] = true;
			_blessingType = static_cast<BlessingType>(i);
		}

		EnableFill(true);
		SetFillColor(0, 0, 0, 0);
		
		InitImages(_blessingType);

		SetImage(_default);
		SetImageStrecth(false);
		SetImageAlignment(H_DIRECTION::CENTER, V_DIRECTION::CENTER);

		AddAnimation(0, &_darkenImageTransition);
		AddAnimation(1, &_brightenImageTransition);

		++count;
	}

	BlessingType GetBlessingType() {
		return _blessingType;
	}

	bool HitTest(int mouseX, int mouseY) {
    return mouseX >= _x && mouseX <= (_x + _width) &&
      mouseY >= _y && mouseY <= (_y + _height);
  }

	void AddEventLister(const char* eventName, std::function<void()> callback) {
    _eventHandlers[eventName] = callback;
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
		_isPressed = true;
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

	void Render(Graphics& g) override {
		Container::Render(g);
	}

private:

	void InitImages(BlessingType blessingType) {
		switch (blessingType)
		{
		case BlessingType::Virago: {
			_default = ResourceManager::Get().GetImage(L"virago");
			_selected = ResourceManager::Get().GetImage(L"virago_selected");
		} break;
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

inline int BlessingContainer::count = 0;
inline bool BlessingContainer::check[BLESSING_TYPE_NUM] = { 0 };

class BlessingsOfGodStateController {
	std::vector<BlessingContainer*> _blessingContainers;
	bool _selectionChanged{ false };
	int _prevSelectedIndex{ -1 };
	int _currSelectedIndex{ -1 };

public:
	BlessingsOfGodStateController() {}

	void AddBlessingContainer(BlessingContainer* bc) {
		int index = _blessingContainers.size();
		bc->AddEventLister("mouseClick", [this, index]() {
			// Check if the same index was selected
			bool condition = index == _currSelectedIndex;
			// Store the prev index
			_prevSelectedIndex = _currSelectedIndex;
			// If yes, the selected index is -1, otherwise, itself.
			_currSelectedIndex = condition * -1 + !condition * index;
			// Mark that the selection change.
			_selectionChanged = true;
		});

    _blessingContainers.push_back(bc);
  }

	BlessingType GetCurrentSelectedBlessingType() {
		if (_currSelectedIndex < 0) return BlessingType::Virago;
		return _blessingContainers[_currSelectedIndex]->GetBlessingType();
	}

	void HandleMouseEvent(int mouseX, int mouseY, bool isDown, bool isUp) {
		for (auto* bc : _blessingContainers) {
      if (bc->HitTest(mouseX, mouseY)) {
        if (isDown) {
          bc->OnMouseDown();
				} else if (isUp) {
					bc->OnMouseUp();
				}
      } else {
        bc->OnMouseLeave();
      }
    }
  }

	void UpdateContainerState(bool &isSelected) {
		if (!_selectionChanged) return;
		_selectionChanged = false;

		if (_currSelectedIndex < 0) {	// When index is -1
			// Reset all
			isSelected = false;
			for (int i = 0; i < _blessingContainers.size(); ++i) {
				auto* bc = _blessingContainers[i];
				if (i == _prevSelectedIndex) {
					bc->SetImage(bc->_default);
				} else {	// If it was darkened
					bc->SetState(1);	// brighten
					bc->_isDarker = false;
				}
			}
		} else {	// Otherwise
			if (!isSelected)
				isSelected = true;
			for (int i = 0; i < _blessingContainers.size(); ++i) {
				auto* bc = _blessingContainers[i];
				// Selected container
				if (i == _currSelectedIndex) {
					// Mark that it is selected
					bc->SetImage(bc->_selected);
					if (bc->_isDarker) {	// If it was darkened
						bc->SetState(1);	// brighten
						bc->_isDarker = false;
					}
					continue;
				}

				// The other containers
				bc->SetImage(bc->_default);
				if (!bc->_isDarker) {	// If it's not darkened
					Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
					bc->SetState(0);	// darken
					bc->_isDarker = true;
				}
			}
		}
	}
};
