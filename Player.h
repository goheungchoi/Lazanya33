#pragma once

#include "IPlayer.h"
#include "CollectiveRenderable.h"
#include "AnimationController.h"

constexpr int PLAYER_DEFAULT_AD = 10;
constexpr double PLAYER_DEFAULT_MAX_OXYGEN_LEVEL = 60;
constexpr int PLAYER_DEFAULT_MAX_HP = 0;
constexpr int PLAYER_DEFAULT_LASGULA_DURATION = 0;
constexpr int PLAYER_DEFAULT_COMBO_DURATION = 1;

/**
 * @brief Example use of AnimationController
 */
class Player : public IPlayer {
	AnimationController* _animationController{nullptr};

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
    _score{0} {}

  /* Getters */
  int GetPositionX() { return _position.X; }
  int GetPositionY() { return _position.Y; }
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
		IRenderable::_position.X = x;
    IRenderable::_position.Y = y;
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
    IRenderable::_position.X += x;
    IRenderable::_position.Y += y;
  }
};
