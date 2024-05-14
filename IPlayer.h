#pragma once

class IPlayer {
public:
  virtual int GetAttack() = 0;
  virtual int GetCurrOxyLevel() = 0;
  virtual int GetCurrHP() = 0;
  virtual int GetCurrPoint() = 0;

  virtual int SetMaxOxygenLevel(int) = 0;
  virtual int SetOxygenLevel(int) = 0;

  virtual int SetMaxHP(int) = 0;
  virtual int SetHP(int) = 0;

  virtual void AddHP(int hp) = 0;
  virtual void AddOxygen(int amountOfOxygen) = 0;
  virtual void AddOxygenSpecialCase(int amountOfOxygen) = 0;
  virtual void AddPoint(int points) = 0;
  virtual void AddPointSpecialCase(int points) = 0;

  virtual bool IsDead() = 0;
};
