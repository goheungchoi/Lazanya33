#pragma once

#include "CollectiveRenderable.h"

class IPlayer : public MultiSpriteRenderable<IPlayer> {
public:
	IPlayer() = delete;
	IPlayer(int x, int y, int w, int h, bool caching)
		: MultiSpriteRenderable<IPlayer>(x, y, w, h, caching) {
#ifndef NDEBUG
		SetBorder(0, 255, 0);
#endif // !NDEBUG
	}
	~IPlayer() {}

  /* Getters */
	virtual int GetPositionX() = 0;
	virtual int GetPositionY() = 0;
  virtual int GetAttackDamage() = 0;
  virtual double GetCurrOxyLevel() = 0;
  virtual int GetCurrHP() = 0;
  virtual int GetCurrScore() = 0;

  /* Setters */
	virtual void SetPosition(int x, int y) = 0;

  virtual void SetAttackDamage(int) = 0;

  virtual void SetMaxOxygenLevel(double) = 0;
  virtual void SetOxygenLevel(double) = 0;

  virtual void SetMaxHP(int) = 0;
  virtual void SetHP(int) = 0;

  virtual void SetLasgulaDuration(double) = 0;
  virtual void SetComboDuration(double) = 0;

  /* Modifiers */
  virtual void AddHP(int hp) = 0;

  virtual void AddOxygen(double amountOfOxygen) = 0;
  virtual void AddOxygenFromOxyBlock(double amountOfOxygen) = 0;
  virtual void AddOxygenSpecialCase(double amountOfOxygen) = 0;

  virtual void AddScore(int score) = 0;
  virtual void AddScoreFromOxyBlock(int score) = 0;
  virtual void AddScoreSpecialCase(int score) = 0;

  virtual bool IsDead() = 0;

  virtual void Move(int x, int y) = 0;
};
