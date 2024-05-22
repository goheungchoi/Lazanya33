#pragma once

#include "IPlayer.h"
//Doing Debug:
#include "DebugConsole.h"
class PlayerOxygenSystem
{
	// Player
	class IPlayer* _player;
	double _amountOfReduceOxy = 0.0;
public:
	PlayerOxygenSystem(IPlayer* player,double ReduceOxyAmount) :
		_player{player},
		_amountOfReduceOxy{ -ReduceOxyAmount }
	{}
	~PlayerOxygenSystem() {}

	double GetAmountOfReduceOxy() { return _amountOfReduceOxy; }

	void ReduceOxygen(const double deltaTime)
	{
		
		_player->AddOxygen(_amountOfReduceOxy*deltaTime);
		
	}

	void UpdateAmountOfRedeuceOxy()
	{
		_amountOfReduceOxy -= static_cast<double>((_player->GetDownMeter() % 50==0) * 2);
	}
};

