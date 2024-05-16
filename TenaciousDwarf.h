#pragma once

#include "PlayerDecorator.h"

class TenaciousDwarf : public PlayerDecorator {
public:
  TenaciousDwarf(IPlayer* player) : PlayerDecorator(player) {
    player->SetMaxHP(40);
  }

  void AddOxygen(double amountOfOxygen) override {
    PlayerDecorator::AddOxygen(amountOfOxygen * 1.25f);
  }
};
