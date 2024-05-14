#pragma once

#include "PlayerDecorator.h"

class Anaerobic : public PlayerDecorator {
public:
  Anaerobic(IPlayer* player) : PlayerDecorator(player) {}

  void AddOxygenFromOxyBlock(float amountOfOxygen) override {
    PlayerDecorator::AddOxygenFromOxyBlock(amountOfOxygen / 2.0f);
  }

  void AddScoreFromOxyBlock(int score) override {
    PlayerDecorator::AddScoreFromOxyBlock(score * 10);
  }
};
