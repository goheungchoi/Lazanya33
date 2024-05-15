#pragma once

#include "IPlayer.h"
#include "Wall.h"

class PlayerBricksInteractionSystem {
// Player*
// Wall*
// WallGenerationSystem*

public:

	PlayerBricksInteractionSystem(
	IPlayer* player, 
	Wall* wall
	/*TODO: WallGenerationSystem*/) {

	}

	void ApplyDamageToBrickByPlayer(int x, int y) {
		// 플레이어가 벽돌에 데미지 입힘

		// 만약 벽돌이 파괴 되면
		// RewardPlayer(int x, int y);
    // DestoryBrick(x, y);
		// If y < _yCap: MovePlayerTo(x, y);
	}

	void RewardPlayer(int x, int y) {
		// 파괴될 벽돌 데이터 수집

		// 플레이어의 양옆 벽돌이 파괴됐으면 (player.y == brick.y)
		// 플레이어 점수 o
		// 
		// 산소 x
	}

	void DestoryBrick(int x, int y) {
		// 벽돌 파괴
	}

	void PopFrontRowOfBricks() {

	}

	void PushBackRowOfBricks() {

	}

	void MovePlayerTo(int x, int y) {

	}

};
