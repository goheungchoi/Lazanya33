#pragma once

#include "PlayerDecorator.h"

class Wimp : public PlayerDecorator {
public:
  Wimp(IPlayer* player) : PlayerDecorator(player) {
    player->SetAttackDamage(9);
  }
};
