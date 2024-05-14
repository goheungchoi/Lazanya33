#pragma once

#include "IPlayer.h"
#include "IRenderable.h"
#include "AnimationController.h"

constexpr int PLAYER_DEFAULT_AD = 0;
constexpr int PLAYER_DEFAULT_MAX_OXYGEN_LEVEL = 0;
constexpr int PLAYER_DEFAULT_MAX_HP = 0;
constexpr int PLAYER_DEFAULT_LASGULA_DURATION = 0;

/**
 * @brief Example use of AnimationController
 */
class Player : public IPlayer, public IRenderable {
	AnimationController* _animationController;

	/* Properties */
private:
  int _ad;
  float _maxOxygenLevel;
  float _oxygenLevel;
  int _maxHP;
  int _hp;
  int _score;

  float _lasgulaDuration;
  float _lasgulaElapsedTime;

  float _comboDuration;
  float _comboElapsedTime;
  int _comboNumber;
 public:

	Player()
  : _ad{PLAYER_DEFAULT_AD},
    _maxOxygenLevel{PLAYER_DEFAULT_MAX_OXYGEN_LEVEL},
    _oxygenLevel{PLAYER_DEFAULT_MAX_OXYGEN_LEVEL},
    _maxHP{PLAYER_DEFAULT_MAX_HP},
    _hp{PLAYER_DEFAULT_MAX_HP},
    _lasgulaDuration(PLAYER_DEFAULT_LASGULA_DURATION),

    _score{0} {}

  /* Getters */
  int GetAttackDamage() override { return _ad; }
  int GetCurrOxyLevel() override { return _oxygenLevel; }
  int GetCurrHP() override { return _hp; }
  int GetCurrScore() override { return _score; }

  /* Setters */
  void SetAttackDamage(int ad) { _ad = ad; };
  void SetMaxOxygenLevel(float maxOxygenLevel) override {
    _maxOxygenLevel = maxOxygenLevel;
  }
  void SetOxygenLevel(float oxygenLevel) override { _oxygenLevel = oxygenLevel; }

  void SetMaxHP(int maxHP) override { _maxHP = maxHP; }
  void SetHP(int hp) override { _hp = (hp <= _maxHP) * hp + (hp > _maxHP) *_maxHP; }

  //TODO: lasgula
  virtual void SetLasgulaDuration(float) = 0;
  
  //TODO: combo
  virtual void SetComboDuration(float) = 0;

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

  void SetLasgulaDuration(float) override {
  
  };
  
  virtual void SetComboDuration(float) = 0;

  bool IsDead() override { return _hp <= 0 || _oxygenLevel <= 0; }

  void Move(int x, int y) override { 
    IRenderable::_position.X += x;
    IRenderable::_position.Y += y;
  }

	void Render(Graphics& g) override {	// TODO: Need to remove const
    // _animationController->GetCurrentFrame()->Render(g);

#ifndef NDEBUG	// 디버깅일 때, 디버그용 사각형을 그림.
		Pen debuggingPen(Color::Red, 5.f);
		g.DrawRectangle(&debuggingPen, Rect(900, 900, 950, 950));
#endif
	}
};
