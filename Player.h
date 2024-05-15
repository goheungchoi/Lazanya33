#pragma once

#include "IPlayer.h"
#include "CollectiveRenderable.h"
#include "AnimationController.h"

constexpr int PLAYER_DEFAULT_AD = 0;
constexpr int PLAYER_DEFAULT_MAX_OXYGEN_LEVEL = 0;
constexpr int PLAYER_DEFAULT_MAX_HP = 0;
constexpr int PLAYER_DEFAULT_LASGULA_DURATION = 0;
constexpr int PLAYER_DEFAULT_COMBO_DURATION = 0;

/**
 * @brief Example use of AnimationController
 */
class Player : public IPlayer {
	AnimationController* _animationController{nullptr};

	/* Properties */
private:
  int _ad;    // Brick Interation
  float _maxOxygenLevel;
  float _oxygenLevel;     // OxygenLevelSystem
  int _maxHP; // N/a
  int _hp;    // N/A
  int _score; // Brick Interation

  float _lasgulaDuration;
  float _lasgulaElapsedTime;

  float _comboDuration;
  float _comboElapsedTime;
  int _comboNumber;
 public:

	Player()
  : IPlayer(2, 2, 120, 240, true),
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

    _score{0} {}

  /* Getters */
  int GetPositionX() { return _position.X; }
  int GetPositionY() { return _position.Y; }
  int GetAttackDamage() override { return _ad; }
  float GetCurrOxyLevel() override { return _oxygenLevel; }
  int GetCurrHP() override { return _hp; }
  int GetCurrScore() override { return _score; }

  /* Setters */
	void SetPosition(int x, int y) {
		IRenderable::_position.X = x;
    IRenderable::_position.Y = y;
	}
  void SetAttackDamage(int ad) { _ad = ad; };
  void SetMaxOxygenLevel(float maxOxygenLevel) override {
    _maxOxygenLevel = maxOxygenLevel;
  }
  void SetOxygenLevel(float oxygenLevel) override { _oxygenLevel = oxygenLevel; }

  void SetMaxHP(int maxHP) override { _maxHP = maxHP; }
  void SetHP(int hp) override { _hp = (hp <= _maxHP) * hp + (hp > _maxHP) *_maxHP; }

  //TODO: lasgula
  void SetLasgulaDuration(float) override { /*TODO*/ }
  
  //TODO: combo
  void SetComboDuration(float) override { /*TODO*/ }

  /* Modifiers */
  void AddHP(int hp) override 
  { _hp = ((hp + _hp) <= _maxHP) * (hp + _hp); }
  void AddOxygen(float amountOfOxygen) override 
  { _oxygenLevel += amountOfOxygen; }
  void AddOxygenFromOxyBlock(float amountOfOxygen) override 
  { AddOxygen(amountOfOxygen); };
  void AddOxygenSpecialCase(float amountOfOxygen) override 
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
