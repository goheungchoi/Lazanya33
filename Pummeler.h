#pragma once

#include "PlayerDecorator.h"

class Pummeler : public PlayerDecorator {
public:
  Pummeler(IPlayer* player) : PlayerDecorator(player) {
   player->SetComboDuration(1.5);
  }
};
