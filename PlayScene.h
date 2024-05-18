#pragma once
#include "SceneGraph.h"

constexpr int GRID_MAP_POSITION_X = 720;
constexpr int GRID_MAP_POSITION_Y = -120;

template<class T>
class SingleSpriteRenderable;
class Container;

class PlayScene :public IScene
{
	class GridMap* _gridMap;
	class IPlayer* _player;
	class Wall* _walls;

	class Container* _letterContainer;
	struct LetterComponents {
		SingleSpriteRenderable<LetterComponents>* background;
		class Container* letter;

		class Container* diagrams;
		class Container* leftArrowDiagram;
		class Container* downArrowDiagram;
		class Container* rightArrowDiagram;
		

		/*class Container* blessOfGod;
		class Container* firstBlessOfGod;*/
	} _letterComponents;

	Container* _ui;
	Container* _uiChild1;
	Container* _uiChild2;
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

