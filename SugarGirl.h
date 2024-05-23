#pragma once

#include "PlayerDecorator.h"

class SugarGirl : public PlayerDecorator {
public:
  SugarGirl(IPlayer* player) : PlayerDecorator(player) {
    player->SetLasgulaDuration(5);
  }
};
