#pragma once

#include "IPlayer.h"
//Doing Debug:
#include "DebugConsole.h"
class PlayerOxygenSystem
{
	// Player
	class IPlayer* _player;
	double _amountOfReduceOxy = 0.0;
	double _initReduceOxy = 0.0;
public:
	PlayerOxygenSystem(IPlayer* player,double ReduceOxyAmount) :
		_player{player},
		_amountOfReduceOxy{ -ReduceOxyAmount },
		_initReduceOxy{ _amountOfReduceOxy }
	{}
	~PlayerOxygenSystem() {}

	double GetAmountOfReduceOxy() { return _amountOfReduceOxy; }

	void ReduceOxygen(const double deltaTime)
	{
		
		_player->AddOxygen(_amountOfReduceOxy*deltaTime);
		
	}

	void ResetReduceOxy()
	{
		_amountOfReduceOxy = _initReduceOxy;
	}

	void UpdateAmountOfRedeuceOxy()
	{
		if(_amountOfReduceOxy<=22)
		_amountOfReduceOxy -= static_cast<double>((_player->GetDownMeter() % 50==0) * 2);
		Debug.Log(_amountOfReduceOxy);
	}
};

