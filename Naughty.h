#pragma once

#include "PlayerDecorator.h"

class Naughty : public PlayerDecorator {
public:
  Naughty(IPlayer* player) : PlayerDecorator(player) {}

  void Move(int x, int y) { PlayerDecorator::Move(y, x); }
};
