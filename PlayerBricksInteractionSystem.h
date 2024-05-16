#pragma once

#include "IPlayer.h"
#include "Wall.h"
#include "Player.h"

class PlayerBricksInteractionSystem {
// Player*
// Wall*
	IPlayer* _player;
	Wall* _wall;
public:
	
	PlayerBricksInteractionSystem(
		IPlayer* player,
		Wall* wall
	) :_player{ player }, _wall{wall} {}

	void ApplyDamageToBrickByPlayer(int row, int col,BYTE key,int& count) {
		//player damage to birck
		_wall->DamageBrick(row, col, _player->GetAttackDamage());
		
		// if brick destory
		if (_wall->GetBrick(row, col).blockHealth <= 0)
		{
			RewardPlayer(row, col);
			_wall->DestroyBrick(row, col);
			_player->SetPosition(col, 4);
			if (key == VK_DOWN)
			{
				_wall->PopFrontBricks();
				count++;
			}
		}
		// RewardPlayer(int row, int col);
    // DestoryBrick(row, col);
	}

	void RewardPlayer(int row, int col) {
		// Collect brick data to be destroyed
		Brick& currBrickData = _wall->GetBrick(row, col);

		//If the broken brick is gold
		if (currBrickData.type == BrickType::GOLD)
		{
			_player->AddScoreSpecialCase(currBrickData.blockScore);

			if (_player->GetPositionY() != row)
			{
				_player->AddOxygenSpecialCase(currBrickData.blockDownAir);
			}
		}

		//If the broken brick is OxyBrick
		else if (currBrickData.type == BrickType::OXYGEN)
		{
			_player->AddScoreFromOxyBlock(currBrickData.blockScore);

			if (_player->GetPositionY() != row)
			{
				_player->AddOxygenFromOxyBlock(currBrickData.blockDownAir);
			}
		}

		//If the broken brick is else thing
		else
		{
			_player->AddScore(_wall->GetBrick(row, col).blockScore);
			
			if (_player->GetPositionY() != row)
			{
				_player->AddOxygen(_wall->GetBrick(row, col).blockDownAir);
			}
		}
		// 플레이어의 양옆 벽돌이 파괴됐으면 (player.y == brick.y) 
		// 플레이어 점수 o
		// 
		// 산소 x
	}

};
