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

	void ApplyDamageToBrickByPlayer(int row, int col) {
		// 플레이어가 벽돌에 데미지 입힘
		_wall->DamageBrick(row, col, _player->GetAttackDamage());
		
		// 만약 벽돌이 파괴 되면
		if (_wall->GetBrick(row, col).block_health <= 0)
		{
			RewardPlayer(row, col);
			_wall->DestroyBrick(row, col);
			if (_player->GetPositionY() < 4)
			{
				_player->SetPosition(col, row);
			}
			else
			{
				_player->SetPosition(4, row);
			}
		}
		// RewardPlayer(int row, int col);
    // DestoryBrick(row, col);
		// If y < _yCap: MovePlayerTo(row,col);
	}

	void RewardPlayer(int row, int col) {
		// 파괴될 벽돌 데이터 수집
		_player->AddScore(_wall->GetBrick(row, col).block_score);
		
		if (_player->GetPositionY() != row)
		{
			_player->AddOxygen(_wall->GetBrick(row, col).block_downAir);
		}
		// 플레이어의 양옆 벽돌이 파괴됐으면 (player.y == brick.y) 
		// 플레이어 점수 o
		// 
		// 산소 x
	}

};
