#pragma once

#include "IPlayer.h"

class PlayerDecorator : public IPlayer {
protected:
  IPlayer* _player;

public:
  PlayerDecorator(IPlayer* player) :IPlayer(2, 2, 1, 1, true), _player{ player } {}

  /* Getters */
  virtual int GetPositionX() override { return _player->GetPositionX(); }
  virtual int GetPositionY() override { return _player->GetPositionY(); }
  virtual int GetAttackDamage() override { return _player->GetAttackDamage(); }
  virtual double GetCurrOxyLevel() override { return _player->GetCurrOxyLevel(); }
  virtual int GetCurrHP() override { return _player->GetCurrHP(); }
  virtual int GetCurrScore() override { return _player->GetCurrScore(); }
  virtual int GetCurrCombo() override { return _player->GetCurrCombo(); }
  virtual double GetComboElapsedTime()override { return _player->GetComboElapsedTime(); }
  virtual double GetComboDuration()override { return _player->GetComboDuration(); }
  virtual int GetDownMeter()override { return _player->GetDownMeter(); }

  /* Setters */
  void SetPosition(int x, int y) { _player->SetPosition(x, y); }
  virtual void SetAttackDamage(int ad) override 
  { _player->SetAttackDamage(ad); };

  virtual void SetMaxOxygenLevel(double maxOxygenLevel) override 
  { _player->SetMaxOxygenLevel(maxOxygenLevel); }
  virtual void SetOxygenLevel(double oxygenLevel) override 
  { _player->SetOxygenLevel(oxygenLevel); }

  virtual void SetMaxHP(int maxHP) override 
  { _player->SetMaxHP(maxHP); }
  virtual void SetHP(int hp) override { _player->SetHP(hp); }

  virtual void SetLasgulaDuration(double lasgulaDuration) 
  { _player->SetLasgulaDuration(lasgulaDuration); }
  virtual void SetComboDuration(double comboDuration) 
  { _player->SetComboDuration(comboDuration); }
  virtual void SetCombo(int combo) override
  {_player->SetCombo(combo);}
  virtual void SetComboElapsedTime(double comboElapsedTime)override 
  { _player->SetComboElapsedTime(comboElapsedTime); }
  virtual void SetDownMeter(int meter)override 
  { _player->SetDownMeter(meter); }


  /* Modifiers */
  virtual void AddHP(int hp) override { _player->AddHP(hp); }

  virtual void AddOxygen(double amountOfOxygen) override 
  { _player->AddOxygen(amountOfOxygen); }
  virtual void AddOxygenFromOxyBlock(double amountOfOxygen) override 
  { _player->AddOxygenFromOxyBlock(amountOfOxygen); };
  virtual void AddOxygenSpecialCase(double amountOfOxygen) override 
  { _player->AddOxygenSpecialCase(amountOfOxygen); }

  virtual void AddScore(int score) override 
  { _player->AddScore(score); }
  virtual void AddScoreFromOxyBlock(int score) override 
  { _player->AddOxygenFromOxyBlock(score); }
  virtual void AddScoreSpecialCase(int score) override 
  { _player->AddScoreSpecialCase(score); }

  virtual void AddCombo()override { _player->AddCombo(); }
  virtual void AddComboElapsedTime(const double& deltaTime)override 
  { _player->AddComboElapsedTime(deltaTime);}
  virtual void AddDownMeter() override { _player->AddDownMeter(); }

  bool IsDead() override { return _player->IsDead(); }

  virtual void Move(int x, int y) override { _player->Move(x, y); }

	virtual void Render(Gdiplus::Graphics& g) override { _player->Render(g); }
};
