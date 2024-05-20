#pragma once
#include "SceneGraph.h"

constexpr int GRID_MAP_POSITION_X = 720;
constexpr int GRID_MAP_POSITION_Y = -120;
constexpr int GRID_ITEM_WIDTH = 120;
constexpr int GRID_ITEM_HEIGHT = 120;

template<class T>
class SingleSpriteRenderable;
class Container;
class BlessingContainer;

class PlayScene :public IScene
{
#ifndef NDEBUG
	Container* _fpsBox;
	double _elapsedTime{ 0.0 };
	std::size_t _frames{ 0 };
	std::size_t _frameRate{ 0 };
#endif

/* Scene Graphics Components */
	
	// Game Play Scene Components
	Container* _gamePlayUIContainer;
	struct GamePlayComponents {
		Container* _leftBox;
		// TODO: Might need to be animated
		Container* daughter;
		Container* husband;
		Container* mother;
		Container* dancingTownspeople;
		Container* ancestors;

		Container* _centerBox;
		Container* oxygenMeter;
		Container* meterBackground;
		Container* oxygenLevel;

		Container* _rightBox;
		Container* scoreBoard;
		Container* gloryOfFamily;
		Container* honorOfAncestor;
		Container* currentHonor;
		Container* currentState;
	} _gamePlayUIComponents;

	SingleSpriteRenderable<class GridMap>* _gridMapBackground;
	class GridMap* _gridMap;
	class IPlayer* _player;
	class Wall* _wall;

	Container* _ui;
	Container* _uiChild1;
	Container* _uiChild2;
	//Variables introduced to add walls when pop 3 times
	int _countWallPop=0;

/* Systems */
	class BrickGenSystem* _brickGenSystem;
	class PlayerOxygenSystem* _playerOxySystem;
	class PlayerBricksInteractionSystem* _playerBrickInteractionSystem;

// TODO: Test Animation
	class Animation* _testAnimation;

public:
	PlayScene();
	~PlayScene();
	
	void Update(double deltaTime) override;
	void Draw() override;
	void InitScene() override;
	void EndScene() override;

private:
	void __InitComponents();
	void __InitSystems();

	void __PlayerUpdate(const double deltaTime);

	std::wstring __WStringifyGloryHall(int glory) {
		wchar_t buffer[30];
		swprintf_s(buffer, L"가문의 영광: %8d", glory);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyMothersHonor(int mother) {
		wchar_t buffer[30];
		swprintf_s(buffer, L"어머니: %18d", mother);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyCurrentHonor(int currentHonor) {
		wchar_t buffer[30];
		swprintf_s(buffer, L"명예: %22d", currentHonor);
		return std::wstring(buffer);
	}

#ifndef NDEBUG
	std::wstring StringifyFrameRate(std::size_t fps) {
		wchar_t buffer[12];
		swprintf_s(buffer, L"fps: %4llu", fps);
		return std::wstring(buffer);
	}
#endif // !NDEBUG
};

