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

	void SetIPlayer(IPlayer* player) {
		_player = player;
	}

	void ApplyDamageToBrickByPlayer(int row, int col,BYTE key,int& count, const double& deltaTime) {
		//player damage to birck
		if (_wall->GetBirckType(row, col) == BrickType::NONE)
		{
			return;
		}

		_wall->DamageBrick(row, col, _player->GetAttackDamage());
		if (_wall->GetBrick(row, col).blockHealth * 2 <= _wall->GetBrick(row, col).maxBlockHealth)
		{
			_wall->_brickSprites.At(row, col) = GetBrickSprite(
				_wall->GetBirckType(row, col), 
				TypeToTag(_wall->GetBirckType(row,col))
			);
		}
		

		// if brick destory
		if (_wall->GetBrick(row, col).blockHealth <= 0)
		{
			PlayBrickDestroySound(_wall->GetBirckType(row, col));
			RewardPlayer(row, col);
			_wall->DestroyBrick(row, col, key == VK_DOWN);
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
			_player->AddOxygenFromOxyBlock(currBrickData.blockDownAir);

			if (_player->GetPositionY() != row)
			{
				//SeoungWoo Change
				_player->AddCombo();
				_player->SetComboElapsedTime(0);
				_player->AddDownMeter();
			}
		}

		else if (currBrickData.type == BrickType::BOMB)
		{
			_player->AddOxygen(currBrickData.blockDownAir);
		}
		
		else if (currBrickData.type == BrickType::RASGULLA)
		{
			_player->TurnOnLasgulaState();
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
		
		// Combo Additional Scores
		switch (_player->GetCurrCombo()) {
			case 0:
			case 1:
				break;
			case 2:
				_player->AddScore(1);		// One additional score
				break;
			case 3:
				_player->AddScore(2);
				break;
			case 4:
				_player->AddScore(3);
				break;
			case 5:
			default:
				_player->AddScore(4);
				break;
		}
	}

	//TODO: bircktype sound play
	void PlayBrickDestroySound(BrickType type){
		switch (type) {
		case BrickType::DEFAULT:
			Music::soundManager->PlayMusic(Music::eSoundList::block00_destroy_Malang, Music::eSoundChannel::Default);
			break;
		case BrickType::STONE:
			Music::soundManager->PlayMusic(Music::eSoundList::block01_destroy_Dan, Music::eSoundChannel::Stone);
			break;
		case BrickType::ROCK:
			Music::soundManager->PlayMusic(Music::eSoundList::block02_destroy_DDak, Music::eSoundChannel::Rock);
			break;
		case BrickType::BOMB:
			Music::soundManager->PlayMusic(Music::eSoundList::Block04_Destroy, Music::eSoundChannel::Bomb);
			break;
		case BrickType::GOLD:
			Music::soundManager->PlayMusic(Music::eSoundList::Block05_destroy_gold, Music::eSoundChannel::Gold);
			break;
		case BrickType::OXYGEN:
			Music::soundManager->PlayMusic(Music::eSoundList::Block06_destroy_air, Music::eSoundChannel::Oxygen);
			break;
		case BrickType::RASGULLA:
			Music::soundManager->PlayMusic(Music::eSoundList::rasgula, Music::eSoundChannel::Lasgulla);
			break;
		}
	}


	std::wstring TypeToTag(BrickType type)
	{
		switch (type)
		{
		case BrickType::DEFAULT:
			return L"B.default";
		case BrickType::STONE:
			return L"B.stone";
		case BrickType::ROCK:
			return L"B.rock";
		case BrickType::BOMB:
			return L"B.bombR";
		case BrickType::GOLD:
			return L"B.gold";
		case BrickType::OXYGEN:
			return L"B.air";
		case BrickType::RASGULLA:
			return L"B.rasgulla";
		case BrickType::GULAB_JAMUN:
			return L"B.gulabjamun";
		}
	}
};
