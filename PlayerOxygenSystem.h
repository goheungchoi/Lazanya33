#pragma once

#include "IPlayer.h"
#include "Timer.h"

class PlayerOxygenSystem
{
	// Player
	class IPlayer* _player;
public:
	PlayerOxygenSystem(IPlayer* player) :_player{player} {}
	~PlayerOxygenSystem() {}

	void ReduceOxygen(const double deltaTime)
	{
		
	}

};

