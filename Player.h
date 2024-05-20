#pragma once

#include "IPlayer.h"
// Need to be GridItem!
#include "CollectiveRenderable.h"

// Animations
#include "AnimationController.h"
#include "Animation.h"

#include "ResourceManager.h"

constexpr int PLAYER_DEFAULT_AD = 10;
constexpr double PLAYER_DEFAULT_MAX_OXYGEN_LEVEL = 60;
constexpr int PLAYER_DEFAULT_MAX_HP = 0;
constexpr int PLAYER_DEFAULT_LASGULA_DURATION = 0;
constexpr int PLAYER_DEFAULT_COMBO_DURATION = 1;

/**
 * @brief Example use of AnimationController
 */
class Player : public IPlayer {
	AnimationController* _animationController;

	/* Properties */
private:
  int _ad;    // Brick Interation
  double _maxOxygenLevel;
  double _oxygenLevel;     // OxygenLevelSystem
  int _maxHP; // N/a
  int _hp;    // N/A
  int _score; // Brick Interation
  int _downMeter;//OxygenLevelSystem

  double _lasgulaDuration;
  double _lasgulaElapsedTime;

  double _comboDuration;
  double _comboElapsedTime;
  int _comboNumber;
 public:

	Player()
  : _ad{PLAYER_DEFAULT_AD},
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
		
		Animation* downAttackAnimation = new Animation(
			// Sprite Sheet
			ResourceManager::Get().GetImage(L"motion_sheet"),
		// X, Y, loop
			0, 0, true
		);
		downAttackAnimation->SliceSpriteSheet(32, 32, 0, 0, 32, 32);
		downAttackAnimation->SetFrameDurations({ 0.08 });

		_animationController = new AnimationController();
		_animationController->AddAnimation(0, downAttackAnimation);
		_animationController->SetState(0);
	}

  /* Getters */
  int GetPositionX() { return _gridPos.X; }
  int GetPositionY() { return _gridPos.Y; }
  int GetAttackDamage() override { return _ad; }
  double GetCurrOxyLevel() override { return _oxygenLevel; }
  int GetCurrHP() override { return _hp; }
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

  //SeoungWoo Change
  void SetCombo(int combo)override { _comboNumber = combo; }
  void SetComboDuration(double comboDuration)override { _comboDuration = comboDuration; }
  void SetDownMeter(int meter)override { _downMeter = meter; }

  //TODO: lasgula
  void SetLasgulaDuration(double) override { /*TODO*/ }
  
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

	void Update(double deltaTime) {
		_animationController->Update(deltaTime);
	}

	void Render(Graphics& g) {
		IPlayer::Render(g);

		g.TranslateTransform(_position.X, _position.Y);
		_animationController->GetCurrentAnimation()->Render(g);
		g.TranslateTransform(-_position.X, -_position.Y);
	}
};
