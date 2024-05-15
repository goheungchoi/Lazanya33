#pragma once

#include "IPlayer.h"

class PlayerDecorator : public IPlayer {
protected:
  IPlayer* _player;

public:
  PlayerDecorator(IPlayer* player) : _player{player} {}

  /* Getters */
	virtual int GetPositionX() override { return _player->GetPositionX(); }
	virtual int GetPositionY() override { return _player->GetPositionY(); }
  virtual int GetAttackDamage() override { return _player->GetAttackDamage(); }
  virtual float GetCurrOxyLevel() override { return _player->GetCurrOxyLevel(); }
  virtual int GetCurrHP() override { return _player->GetCurrHP(); }
  virtual int GetCurrScore() override { return _player->GetCurrScore(); }

  /* Setters */
  void SetPosition(int x, int y) { _player->SetPosition(x, y); }
  virtual void SetAttackDamage(int ad) override 
  { _player->SetAttackDamage(ad); };

  virtual void SetMaxOxygenLevel(float maxOxygenLevel) override 
  { _player->SetMaxOxygenLevel(maxOxygenLevel); }
  virtual void SetOxygenLevel(float oxygenLevel) override 
  { _player->SetOxygenLevel(oxygenLevel); }

  virtual void SetMaxHP(int maxHP) override 
  { _player->SetMaxHP(maxHP); }
  virtual void SetHP(int hp) override { _player->SetHP(hp); }

  virtual void SetLasgulaDuration(float lasgulaDuration) 
  { _player->SetLasgulaDuration(lasgulaDuration); }
  virtual void SetComboDuration(float comboDuration) 
  { _player->SetComboDuration(comboDuration); }

  /* Modifiers */
  virtual void AddHP(int hp) override { _player->AddHP(hp); }

  virtual void AddOxygen(float amountOfOxygen) override 
  { _player->AddOxygen(amountOfOxygen); }
  virtual void AddOxygenFromOxyBlock(float amountOfOxygen) override 
  { _player->AddOxygenFromOxyBlock(amountOfOxygen); };
  virtual void AddOxygenSpecialCase(float amountOfOxygen) override 
  { _player->AddOxygenSpecialCase(amountOfOxygen); }

  virtual void AddScore(int score) override 
  { _player->AddScore(score); }
  virtual void AddScoreFromOxyBlock(int score) override 
  { _player->AddOxygenFromOxyBlock(score); }
  virtual void AddScoreSpecialCase(int score) override 
  { _player->AddScoreSpecialCase(score); }

  bool IsDead() override { return _player->IsDead(); }

  virtual void Move(int x, int y) override { _player->Move(x, y); }
};
