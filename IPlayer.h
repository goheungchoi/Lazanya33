#pragma once

#include "CollectiveRenderable.h"

class IPlayer : public CollectiveRenderable<IPlayer> {
public:
	IPlayer() = delete;
	IPlayer(int x, int y, int w, int h, bool caching)
		: CollectiveRenderable<IPlayer>(x, y, w, h, caching) {
		SetBorder(0, 255, 0);
		//SetFillColor(0, 0, 0);
	}
	~IPlayer() {}

  /* Getters */
	virtual int GetPositionX() = 0;
	virtual int GetPositionY() = 0;
  virtual int GetAttackDamage() = 0;
  virtual double GetCurrOxyLevel() = 0;
  virtual int GetCurrHP() = 0;
  virtual int GetCurrScore() = 0;
  //SeoungWoo Change
  virtual int GetCurrCombo() = 0;
  virtual double GetComboElapsedTime() = 0;
  virtual double GetComboDuration() = 0;
  virtual int GetDownMeter() = 0;

  /* Setters */
	virtual void SetPosition(int x, int y) = 0;

  virtual void SetAttackDamage(int) = 0;

  virtual void SetMaxOxygenLevel(double) = 0;
  virtual void SetOxygenLevel(double) = 0;

  virtual void SetMaxHP(int) = 0;
  virtual void SetHP(int) = 0;

  //SeoungWoo Change
  virtual void SetCombo(int) = 0;
  virtual void SetComboDuration(double) = 0;
  virtual void SetDownMeter(int) = 0;


  virtual void SetLasgulaDuration(double) = 0;
  virtual void SetComboElapsedTime(double) = 0;

  /* Modifiers */
  //SeoungWoo Change
  virtual void AddCombo() = 0;
  virtual void AddComboElapsedTime(const double&) = 0;
  virtual void AddDownMeter() = 0;

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
