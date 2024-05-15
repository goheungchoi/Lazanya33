#pragma once
#include "SceneGraph.h"

constexpr int GRID_MAP_POSITION_X = 720;
constexpr int GRID_MAP_POSITION_Y = -120;

class PlayScene :public IScene
{
	class GridMap* _gridMap;
	class IPlayer* _player;
	class Wall* _walls;

/* Systems */
	class BrickGenSystem* _brickGenSystem;

public:
	PlayScene();
	~PlayScene() {};
	
	void Update(double DeltaTime)override;
	void Draw()override;
};

