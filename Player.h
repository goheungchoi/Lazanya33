#pragma once

#include "IPlayer.h"
// Need to be GridItem!
#include "CollectiveRenderable.h"

// Animations
#include "AnimationController.h"
#include "Animation.h"

#include "ResourceManager.h"

constexpr int PLAYER_DEFAULT_AD = 10;
constexpr double PLAYER_DEFAULT_MAX_OXYGEN_LEVEL = 80;
constexpr int PLAYER_DEFAULT_MAX_HP = 100;
constexpr int PLAYER_DEFAULT_LASGULA_DURATION = 3;
constexpr int PLAYER_DEFAULT_COMBO_DURATION = 1;

/**
 * @brief Example use of AnimationController
 */
class Player : public IPlayer {
	AnimationController* _effectController;

	/* Properties */
private:
	int& _x;
	int& _y;

  int _ad;    // Brick Interation
  double _maxOxygenLevel;
  double _oxygenLevel;     // OxygenLevelSystem
  int _maxHP; // N/a
  int _hp;    // N/A
  int _score; // Brick Interation
  int _downMeter;//OxygenLevelSystem

	int _tmp{ 0 };
  double _lasgulaDuration;
  double _lasgulaElapsedTime;
	double _lasgulaEffectInterval{ 0.2 };
	double _lasgulaEffectElapsedTime{ 0.2 };
	bool _lasgulaEffectBool{ false };
	bool _isLasgula{ false };

  double _comboDuration;
  double _comboElapsedTime;
  int _comboNumber;

	bool _downBool{ false };
	bool _leftBool{ false };
	bool _rightBool{ false };

public:
	Player()
  : _x{_position.X}, _y{_position.Y},
		_ad{PLAYER_DEFAULT_AD},
    _maxOxygenLevel{PLAYER_DEFAULT_MAX_OXYGEN_LEVEL},
    _oxygenLevel{PLAYER_DEFAULT_MAX_OXYGEN_LEVEL},
    _maxHP{PLAYER_DEFAULT_MAX_HP},
    _hp{PLAYER_DEFAULT_MAX_HP},
    _lasgulaDuration{PLAYER_DEFAULT_LASGULA_DURATION},
    _lasgulaElapsedTime {0.0f},
    _comboDuration {PLAYER_DEFAULT_COMBO_DURATION},
    _comboElapsedTime {0.0f},
    _comboNumber {0},
    _downMeter{0},
    _score{0} {
		
		Animation* downAttackAnimation1 = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"effect_swordtrail_down_1"),
		// X, Y, loop
			0, 110, false
		);
		downAttackAnimation1->SliceSpriteSheet(120, 120, 0, 0, 0, 0);
		downAttackAnimation1->SetFrameDurations({ 0.08 });
		downAttackAnimation1->EnableBorder(true);
		downAttackAnimation1->SetBorder(255, 255, 0);

		Animation* downAttackAnimation2 = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"effect_swordtrail_down_2"),
		// X, Y, loop
			0, 110, false
		);
		downAttackAnimation2->SliceSpriteSheet(120, 120, 0, 0, 0, 0);
		downAttackAnimation2->SetFrameDurations({ 0.08 });


		Animation* leftAttackAnimation1 = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"effect_swordtrail_left_1"),
		// X, Y, loop
			-110, 0, false
		);
		leftAttackAnimation1->SliceSpriteSheet(120, 120, 0, 0, 0, 0);
		leftAttackAnimation1->SetFrameDurations({ 0.08 });

		Animation* leftAttackAnimation2 = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"effect_swordtrail_left_2"),
		// X, Y, loop
			-110, 0, false
		);
		leftAttackAnimation2->SliceSpriteSheet(120, 120, 0, 0, 0, 0);
		leftAttackAnimation2->SetFrameDurations({ 0.08 });


		Animation* rightAttackAnimation1 = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"effect_swordtrail_right_1"),
		// X, Y, loop
			110, 0, false
		);
		rightAttackAnimation1->SliceSpriteSheet(120, 120, 0, 0, 0, 0);
		rightAttackAnimation1->SetFrameDurations({ 0.08 });

		Animation* rightAttackAnimation2 = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"effect_swordtrail_right_2"),
		// X, Y, loop
			110, 0, false
		);
		rightAttackAnimation2->SliceSpriteSheet(120, 120, 0, 0, 0, 0);
		rightAttackAnimation2->SetFrameDurations({ 0.08 });


		_effectController = new AnimationController();
		_effectController->AddAnimation(
			PlayerEffect::DOWN_ATTACK1, 
			downAttackAnimation1
		);
		_effectController->AddAnimation(
			PlayerEffect::DOWN_ATTACK2, 
			downAttackAnimation2
		);
		_effectController->AddAnimation(
			PlayerEffect::LEFT_ATTACK1, 
			leftAttackAnimation1
		);
		_effectController->AddAnimation(
			PlayerEffect::LEFT_ATTACK2, 
			leftAttackAnimation2
		);
		_effectController->AddAnimation(
			PlayerEffect::RIGHT_ATTACK1, 
			rightAttackAnimation1
		);
		_effectController->AddAnimation(
			PlayerEffect::RIGHT_ATTACK2, 
			rightAttackAnimation2
		);
	}

	~Player() {

	}

  /* Getters */
	IPlayer* GetPlayer() override { return this; };

  int GetPositionX() { return _gridPos.X; }
  int GetPositionY() { return _gridPos.Y; }
  int GetAttackDamage() override { return _ad; }
  double GetCurrOxyLevel() override { return _oxygenLevel; }
	double GetMaxOxyLevel() override { return _maxOxygenLevel; }
  int GetCurrHP() override { return _hp; }
	int GetMaxHP() override { return _maxHP; }
  int GetCurrScore() override { return _score; }
  //SeoungWoo Change
  int GetCurrCombo() override { return _comboNumber; }
  double GetComboElapsedTime() override { return _comboElapsedTime; }
  double GetComboDuration() override { return _comboDuration; }
  int GetDownMeter()override { return _downMeter; }

  /* Setters */
	void SetPosition(int x, int y) {
		SetGridPos(x, y);
	}
  void SetAttackDamage(int ad) { _ad = ad; };
  void SetMaxOxygenLevel(double maxOxygenLevel) override {
    _maxOxygenLevel = maxOxygenLevel;
  }
  void SetOxygenLevel(double oxygenLevel) override { _oxygenLevel = oxygenLevel; }

  void SetMaxHP(int maxHP) override { _maxHP = maxHP; }
  void SetHP(int hp) override { _hp = (hp <= _maxHP) * hp + (hp > _maxHP) *_maxHP; }
	void SetScore(int score) { _score = score; }
  //SeoungWoo Change
  void SetCombo(int combo)override { _comboNumber = combo; }
  void SetComboDuration(double comboDuration)override { _comboDuration = comboDuration; }
  void SetDownMeter(int meter)override { _downMeter = meter; }

  //TODO: lasgula
  void SetLasgulaDuration(double lasgulaDuration) override { 
		_lasgulaDuration = lasgulaDuration;
	}
	void UpdateLasgulaState(double dt) override {
		if (!_isLasgula) return;

		_lasgulaElapsedTime += dt;
		_lasgulaEffectElapsedTime += dt;

		while (_lasgulaEffectElapsedTime >= _lasgulaEffectInterval) {
			_lasgulaEffectElapsedTime -= _lasgulaEffectInterval;

			if (!_lasgulaEffectBool) {
				SetImageIntensity(5.0f, 3.0f, 0.5f);
			}
			else {
				SetImageIntensity(1.f, 1.f, 1.f);
			}
			_lasgulaEffectBool = !_lasgulaEffectBool;
		}

		if (_lasgulaElapsedTime >= _lasgulaDuration) {
			ResetLasgulaChanges();
		}
	}

	void TurnOnLasgulaState() override {
		_isLasgula = true;
		_tmp = GetAttackDamage();
		SetAttackDamage(100);
	}

	bool IsLasgula() override {
		return _isLasgula;
	}

	void ResetLasgulaChanges() override {
		SetAttackDamage(_tmp);
		SetImageIntensity(1.f, 1.f, 1.f);
		_lasgulaEffectElapsedTime = _lasgulaEffectInterval;
		_lasgulaElapsedTime = 0;
		_isLasgula = false;
	}

  
  //TODO: combo
  void SetComboElapsedTime(double comboElapsedTime) override { _comboElapsedTime = comboElapsedTime; }
  /* Modifiers */
  //SeoungWoo Change
  void AddCombo()override { _comboNumber++; }
  void AddComboElapsedTime(const double& deltaTime) override{ _comboElapsedTime += deltaTime; }
  void AddDownMeter()override { _downMeter++; }

  void AddHP(int hp) override 
  { 
    int newHP = hp + _hp;
    _hp = (newHP <= _maxHP) * newHP + (newHP > _maxHP) * _maxHP; 
  }
  void AddOxygen(double amountOfOxygen) override 
  {
    double newOxygen = amountOfOxygen + _oxygenLevel;
    _oxygenLevel = 
      (newOxygen <= _maxOxygenLevel) * newOxygen + (newOxygen > _maxOxygenLevel)*_maxOxygenLevel;
   
  }
  void AddOxygenFromOxyBlock(double amountOfOxygen) override 
  { AddOxygen(amountOfOxygen); };
  void AddOxygenSpecialCase(double amountOfOxygen) override 
  { AddOxygen(amountOfOxygen); };
  
  void AddScore(int score) override { _score += score; }
  void AddScoreFromOxyBlock(int score) override { AddScore(score); }
  void AddScoreSpecialCase(int score) override { AddScore(score); }

  bool IsDead() override { return _hp <= 0 || _oxygenLevel <= 0; }

  void Move(int x, int y) override { 
    _gridPos.X += x;
    _gridPos.Y += y;
  }

	void Update(double deltaTime) override {
		_effectController->Update(deltaTime);
	}

	void Reset() override {
		_effectController->Reset();
	}

	void TriggerEffect(PlayerEffect effect) override {
		_effectController->SetState(effect);
	}

	void DownKeyPressed() {
		_downBool = !_downBool;
		_effectController->SetState(!_downBool);
	}

	bool GetDownBool() {
		return _downBool;
	}

	void LeftKeyPressed() {
		_leftBool = !_leftBool;
		_effectController->SetState(!_leftBool + 2);
	}

	bool GetLeftBool() {
		return _leftBool;
	}

	void RightKeyPressed() {
		_rightBool = !_rightBool;
		_effectController->SetState(!_rightBool + 4);
	}

	bool GetRightBool() {
		return _rightBool;
	}

	void Render(Graphics& g) {
		IPlayer::Render(g);

		auto* effect = _effectController->GetCurrentAnimation();
		if (effect) {
			effect->SetPosition(effect->GetX() + _x, effect->GetY() + _y);
			effect->Render(g);
			effect->SetPosition(effect->GetX() - _x, effect->GetY() - _y);
		}
	}
};
