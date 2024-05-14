#pragma once

#include "IPlayer.h"
#include "IRenderable.h"
#include "AnimationController.h"

constexpr int PLAYER_DEFAULT_AD = 0;
constexpr int PLAYER_DEFAULT_MAX_OXYGEN_LEVEL = 0;
constexpr int PLAYER_DEFAULT_MAX_HP = 0;

/**
 * @brief Example use of AnimationController
 */
class Player : public IPlayer, public IRenderable {
	AnimationController* _animationController;

	/* Properties */
private:
  int _ad;
  int _maxOxygenLevel;
  int _oxygenLevel;
  int _maxHP;
  int _hp;
  int _points;

  int _lasgulaDuration;
  int _lasgulaElapsedTime;

  int _comboDuration;
  int _comboElapsedTime;
  int _comboNumber;
 public:

	Player()
  : _ad{PLAYER_DEFAULT_AD},
    _maxOxygenLevel{PLAYER_DEFAULT_MAX_OXYGEN_LEVEL},
    _oxygenLevel{PLAYER_DEFAULT_MAX_OXYGEN_LEVEL},
    _maxHP{PLAYER_DEFAULT_MAX_HP},
    _hp{PLAYER_DEFAULT_MAX_HP},
    _points{0} {}

  int GetAttack() override { return _ad; }
  int GetCurrOxyLevel() override { return _oxygenLevel; }
  int GetCurrHP() override { return _hp; }
  int GetCurrPoint() override { return _points; }

  int SetMaxOxygenLevel(int maxOxygenLevel) override {
    _maxOxygenLevel = maxOxygenLevel;
  }
  int SetOxygenLevel(int oxygenLevel) override { _oxygenLevel = oxygenLevel; }

  int SetMaxHP(int maxHP) override { _maxHP = maxHP; }
  int SetHP(int hp) override { _hp = (hp <= _maxHP) * hp + (hp > _maxHP) *_maxHP; }

  void AddHP(int hp) override { _hp = ((hp + _hp) <= _maxHP) * (hp + _hp); }
  void AddOxygen(int amountOfOxygen) override { _oxygenLevel += amountOfOxygen; }
  void AddOxygenSpecialCase(int amountOfOxygen) override { AddOxygen(amountOfOxygen); };
  void AddPoint(int points) override { _points += points; }
  void AddPointSpecialCase(int points) override { AddPoint(points); }

  //TODO: lasgula
  //TODO: combo

  bool IsDead() override { return _hp <= 0 || _oxygenLevel <= 0; }

	void Render(Graphics& g) override {	// TODO: Need to remove const
    // _animationController->GetCurrentFrame()->Render(g);

#ifndef NDEBUG	// 디버깅일 때, 디버그용 사각형을 그림.
		Pen debuggingPen(Color::Red, 5.f);
		g.DrawRectangle(&debuggingPen, Rect(900, 900, 950, 950));
#endif
	}
};
