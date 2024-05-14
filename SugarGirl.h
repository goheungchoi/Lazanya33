#pragma once

#include "PlayerDecorator.h"

class SugarGirl : public PlayerDecorator {
public:
  SugarGirl(IPlayer* player) : PlayerDecorator(player) {
    player->SetLasgulaDuration(5);
  }

  void AddOxygen(float amountOfOxygen) override {
    PlayerDecorator::AddOxygen(amountOfOxygen * 1.25f);
  }
};
