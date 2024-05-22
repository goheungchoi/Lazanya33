#pragma once

// TODO: Need to be GridItem!
#include "GridItem.h"

enum PlayerEffect {
	DOWN_ATTACK1,
	DOWN_ATTACK2,
	LEFT_ATTACK1,
	LEFT_ATTACK2,
	RIGHT_ATTACK1,
	RIGHT_ATTACK2
};

class IPlayer : public GridItem {
public:
	
	~IPlayer() {}

	virtual IPlayer* GetPlayer() = 0;

  /* Getters */
	virtual int GetPositionX() = 0;
	virtual int GetPositionY() = 0;
  virtual int GetAttackDamage() = 0;
  virtual double GetCurrOxyLevel() = 0;
	virtual double GetMaxOxyLevel() = 0;
  virtual int GetCurrHP() = 0;
	virtual int GetMaxHP() = 0;
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
  virtual void SetScore(int) = 0;
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

	virtual void TriggerEffect(PlayerEffect) = 0;

	virtual void DownKeyPressed() = 0;

	virtual bool GetDownBool() = 0;

	virtual void LeftKeyPressed() = 0;

	virtual bool GetLeftBool() = 0;

	virtual void RightKeyPressed() = 0;

	virtual bool GetRightBool() = 0;

	virtual void Update(double deltaTime) = 0;
};
