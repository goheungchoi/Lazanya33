#pragma once

#include "IPlayer.h"
//Doing Debug:
#include "DebugConsole.h"
class PlayerOxygenSystem
{
	// Player
	class IPlayer* _player;
	double _reducedESTime=0.0;
	double _amountOfReduceOxy = 0.0;
public:
	PlayerOxygenSystem(IPlayer* player,double ReduceOxyAmount) :
		_player{player},
		_amountOfReduceOxy{ -ReduceOxyAmount }
	{}
	~PlayerOxygenSystem() {}

	void ReduceOxygen(const double deltaTime)
	{
		//_reducedESTime += deltaTime;
		
		_player->AddOxygen(_amountOfReduceOxy*deltaTime);

		//Doing Debug:
		Debug.Log(_player->GetCurrOxyLevel());
		Debug.Log(_amountOfReduceOxy);
	}

};

