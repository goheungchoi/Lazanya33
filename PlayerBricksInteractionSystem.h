#pragma once

#include "IPlayer.h"
#include "Wall.h"
#include "Player.h"
#include "PlayerOxygenSystem.h"
//Doing Debug:
#include "DebugConsole.h"

class PlayerBricksInteractionSystem {
// Player*
// Wall*
	IPlayer* _player;
	Wall* _wall;
	PlayerOxygenSystem* _playerOxySystem;
public:
	PlayerBricksInteractionSystem(
		IPlayer* player,
		Wall* wall,
		PlayerOxygenSystem* playerOxySystem
	) :_player{ player }, _wall{ wall }, _playerOxySystem{ playerOxySystem } {}

	void ApplyDamageToBrickByPlayer(int row, int col,BYTE key,int& count, const double& deltaTime) {
		//player damage to birck
		_wall->DamageBrick(row, col, _player->GetAttackDamage());
		
		// if brick destory
		if (_wall->GetBrick(row, col).blockHealth <= 0)
		{
			PlayBrickDestroySound(_wall->GetBirckType(row, col));
			RewardPlayer(row, col);
			_wall->DestroyBrick(row, col);
			_player->SetPosition(col, 4);
			if (key == VK_DOWN)
			{
				_playerOxySystem->UpdateAmountOfRedeuceOxy();
				_wall->PopFrontBricks();
				count++;
			}
		}
		else
			Music::soundManager->PlayMusic(Music::eSoundList::blockDamage, Music::eSoundChannel::BrickDamage);
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
				//SeoungWoo Change
				_player->AddCombo();
				_player->SetComboElapsedTime(0);
				_player->AddDownMeter();
			}
		}

		//If the broken brick is OxyBrick
		else if (currBrickData.type == BrickType::OXYGEN)
		{
			_player->AddScoreFromOxyBlock(currBrickData.blockScore);

			if (_player->GetPositionY() != row)
			{
				_player->AddOxygenFromOxyBlock(currBrickData.blockDownAir);
				//SeoungWoo Change
				_player->AddCombo();
				_player->SetComboElapsedTime(0);
				_player->AddDownMeter();
			}
		}

		//If the broken brick is else thing
		else
		{
			_player->AddScore(_wall->GetBrick(row, col).blockScore);
			
			if (_player->GetPositionY() != row)
			{
				_player->AddOxygen(_wall->GetBrick(row, col).blockDownAir);
				//SeoungWoo Change
				_player->AddCombo();
				_player->SetComboElapsedTime(0);
				_player->AddDownMeter();
			}
		}
		// 플레이어의 양옆 벽돌이 파괴됐으면 (player.y == brick.y) 
		// 플레이어 점수 o
		// 
		// 산소 x
	}

	//TODO: bircktype sound play
	void PlayBrickDestroySound(BrickType type){
		switch (type) {
		case BrickType::DEFAULT:
			Music::soundManager->PlayMusic(Music::eSoundList::block00_destroy_Malang, Music::eSoundChannel::BrickDestory);
		}
	}
};
