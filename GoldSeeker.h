#pragma once

#include "PlayerDecorator.h"

class SugarGirl : public PlayerDecorator {
public:
  SugarGirl(IPlayer* player) : PlayerDecorator(player) {}

  void AddScoreSpecialCase(int points) override {
    PlayerDecorator::AddScoreSpecialCase(points + 10);
  }

  void AddOxygenSpecialCase(float amountOfOxygen) override {
    PlayerDecorator::AddOxygenSpecialCase(amountOfOxygen + 8.0f);
  }

  void AddOxygen(float amountOfOxygen) override {
    PlayerDecorator::AddOxygen(amountOfOxygen * 0.8f);
  }
};
