#pragma once
#include "SceneGraph.h"

constexpr int GRID_MAP_POSITION_X = 720;
constexpr int GRID_MAP_POSITION_Y = -120;

class PlayScene :public IScene
{
	class GridMap* _gridMap;
	class IPlayer* _player;
	class Wall* _walls;
	class UIComponent* _ui;
	//Variables introduced to add walls when pop 3 times
	int _countWallPop=0;

/* Systems */
	class BrickGenSystem* _brickGenSystem;
	class PlayerOxygenSystem* _playerOxySystem;
	class PlayerBricksInteractionSystem* _playerBrickInteractionSystem;
public:
	PlayScene();
	~PlayScene() {};
	
	void Update(double deltaTime)override;
	void Draw()override;
	void InitScene()override;
	void EndScene()override;
	void PlayerUpdate(const double deltaTime);
};

