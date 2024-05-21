﻿#pragma once
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
		Container* levelUpSign;
		Container* startMessage;
		Container* adBox;
		Container* adValue;
		Container* comboBox;
		Container* comboValue;

		Container* oxygenMeter;
		Container* meterBackground;
		Container* oxygenLevel;

		Container* _rightBox;
		Container* scoreBoard;
		Container* gloryOfFamily;
		Container* honorOfAncestor;
		Container* currentHonor;
		// Next row
		Container* extraInfo;
		Container* additionalScore;
		Container* depth;

		// State Display
		class PlayerStateContainer* currentState;
	} _uiComps;

	SingleSpriteRenderable<class GridMap>* _gridMapBackground;
	class GridMap* _gridMap;
	class IPlayer* _player;
	class Wall* _wall;

	// Game End Scene Components
	Container* _gameEndSceneContainer;
	struct GameEndComponents {
		SingleSpriteRenderable<class GameEndComponents>* gameEndBG;
		Container* textBox;
		Container* text1;
		Container* text2;
		Container* text3;

	} _endComps;

	//Variables introduced to add walls when pop 3 times
	int _countWallPop=0;

/* Systems */
	class BrickGenSystem* _brickGenSystem;
	class PlayerOxygenSystem* _playerOxySystem;
	class PlayerBricksInteractionSystem* _playerBrickInteractionSystem;

/* Game States */
	int _mothersScore{ 70 };
	int _gloryOfFamilyScore{ 80 };

	double _stateUpdateDuration{ 1.0 };
	double _stateUpdateElapsedTime{ 0.0 };
	int _buttonPressedCount{ 0 };

	bool _npcEmerged[5] = { false, };

	bool _initialized{ false };	// Check if the game is reset
	bool _started{ false };	// Check if the game is started by player's action
	double _delayEnding{ 0.0 };
	bool _ended{ false };	//

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

	void __ResetGame();

	void __PlayerUpdate(const double deltaTime);
	void __TriggerNPCsAnimations();

	std::wstring __WStringifyGloryHall(int glory) {
		wchar_t buffer[32];
		swprintf_s(buffer, L"%30d", glory);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyMothersHonor(int mother) {
		wchar_t buffer[32];
		swprintf_s(buffer, L"%30d", mother);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyCurrentHonor(int currentHonor) {
		wchar_t buffer[32];
		swprintf_s(buffer, L"%30d", currentHonor);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyAD(int currentAD) {
		wchar_t buffer[5];
		swprintf_s(buffer, L"%d", currentAD);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyCombos(int combos) {
		wchar_t buffer[5];
		swprintf_s(buffer, L"%d", combos);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyDepth(int depth) {
		wchar_t buffer[5];
		swprintf_s(buffer, L"%dm", depth);
		return std::wstring(buffer);
	}

	std::wstring __WStringifyEndingMessage1();

	std::wstring __WStringifyEndingMessage2_1();
	std::wstring __WStringifyEndingMessage2_2();
	std::wstring __WStringifyEndingMessage2_3();
	
	std::wstring __WStringifyEndingMessage3();

#ifndef NDEBUG
	std::wstring StringifyFrameRate(std::size_t fps) {
		wchar_t buffer[12];
		swprintf_s(buffer, L"fps: %4llu", fps);
		return std::wstring(buffer);
	}
#endif // !NDEBUG
};

