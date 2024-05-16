#pragma once

#include "CollectiveRenderable.h"

class IPlayer : public CollectiveRenderable<IPlayer> {
public:
	IPlayer() = delete;
	IPlayer(int x, int y, int w, int h, bool caching)
		: CollectiveRenderable<IPlayer>(x, y, w, h, caching) {
		SetBorder(0, 255, 0);
		SetFillColor(0, 0, 0);
	}
	~IPlayer() {}

  /* Getters */
	virtual int GetPositionX() = 0;
	virtual int GetPositionY() = 0;
  virtual int GetAttackDamage() = 0;
  virtual float GetCurrOxyLevel() = 0;
  virtual int GetCurrHP() = 0;
  virtual int GetCurrScore() = 0;

  /* Setters */
	virtual void SetPosition(int x, int y) = 0;

  virtual void SetAttackDamage(int) = 0;

  virtual void SetMaxOxygenLevel(float) = 0;
  virtual void SetOxygenLevel(float) = 0;

  virtual void SetMaxHP(int) = 0;
  virtual void SetHP(int) = 0;

  virtual void SetLasgulaDuration(float) = 0;
  virtual void SetComboDuration(float) = 0;

  /* Modifiers */
  virtual void AddHP(int hp) = 0;

  virtual void AddOxygen(float amountOfOxygen) = 0;
  virtual void AddOxygenFromOxyBlock(float amountOfOxygen) = 0;
  virtual void AddOxygenSpecialCase(float amountOfOxygen) = 0;

  virtual void AddScore(int score) = 0;
  virtual void AddScoreFromOxyBlock(int score) = 0;
  virtual void AddScoreSpecialCase(int score) = 0;

  virtual bool IsDead() = 0;

  virtual void Move(int x, int y) = 0;
};
