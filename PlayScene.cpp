#include "pch.h"
#include "PlayScene.h"
#include "GridMap.h"
#include "Player.h"
#include "Wall.h"
#include "Container.h"

//decorator
#include "TenaciousDwarf.h"
#include "Wimp.h"
#include "Pummeler.h"
#include "SugarGirl.h"
#include "Anaerobic.h"
#include "Naughty.h"
#include "GoldSeeker.h"

//system
#include "BrickGenerationSystem.h"
#include "PlayerBricksInteractionSystem.h"
#include "PlayerOxygenSystem.h"

#include "ResourceManager.h"

constexpr double PLAYER_OXYGEN_REDUCE_INITAL_VALUE = 10.0;

PlayScene::PlayScene()
	: _gridMap{ new GridMap(
			GRID_MAP_POSITION_X,
			GRID_MAP_POSITION_Y,
			wallNumRows, wallNumCols, 120, 120) },
	_player{ new Player() },
	_walls{ new Wall() },
	_brickGenSystem{ new BrickGenSystem(_walls) },
	_playerOxySystem{ new PlayerOxygenSystem(_player,PLAYER_OXYGEN_REDUCE_INITAL_VALUE) },
	_playerBrickInteractionSystem{ new PlayerBricksInteractionSystem(_player,_walls,_playerOxySystem)}
{	
	_player->BindSpriteWithTag(
		ResourceManager::Get().GetImage(L"test_asset"),
		L"player"
	);
	
	_ui = new Container(100, 100, 100, 100);
	_ui->SetDisplay(Display::FLEX);
	_ui->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_ui->SetFlexJustifyContent(FlexJustifyContent::FLEX_START);
	_uiChild1 = new Container(20, 20, 20, 20);
	_uiChild1->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_uiChild2 = new Container(60, 60, 20, 20);
	_ui->AddChildComponent(_uiChild1);
	_ui->AddChildComponent(_uiChild2);
	_uiChild1->EnableBorder(true);
	_uiChild1->SetBorder(0, 255, 0);
	_uiChild2->EnableBorder(true);
	_uiChild2->SetBorder(0, 0, 255);
	_ui->EnableBorder(true);
	_ui->SetBorder(255, 0, 0);
	_ui->SetText(L"Hello!");
	_ui->SetRotationPivot(_ui->GetCenterX(), _ui->GetCenterY());
	_gridMap->AttachChildRenderable(_walls);
	_gridMap->AttachChildRenderable(_player);
	_renderSystem->RegisterRenderableObject(_ui);
	_renderSystem->RegisterRenderableObject(_gridMap);
	_renderSystem->CacheDataInRegistry();

	_player->SetCurrentTag(L"player");
	_player = new GoldSeeker(_player);
}

void PlayScene::Update(const double deltaTime)
{
	//if Didn't init, init one time
	if (!DidInit)
	{
		InitScene();
		DidInit = true;
	}

	_ui->Rotate(deltaTime*100);
	PlayerUpdate(deltaTime);
	

#ifdef PLAYSCENE
	if (/*!가족력을 선택했는가?*/)
	{
		//TODO: 가족력 선택 이전의 업데이트.

		_renderSystem->ClearRenderableRegistry();

		//게임 시작시 필요한renderer등록
		_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(player));
	}
	else//가족력을 골랐다면
	{
		/*player=new Decorators*/
		//TODO: 실제 게임 업데이트
	}
#endif
}

void PlayScene::Draw()
{
	_renderSystem->Render();
#ifdef PLAYSCENE
	if (/*!가족력을 선택했는가?*/)
	{

		_renderSystem->Render();
		//TODO: 가족력 선택 이전의 업데이트.
	}
	else//가족력을 골랐다면
	{
		_renderSystem->Render();
		//TODO: 실제 게임 렌더
	}
#endif
}

void PlayScene::InitScene()
{
	_player->SetPosition(2, 4);
	_brickGenSystem->BrickGenInit();
	//가족력 선택 이전에 필요한 RenderableObject 등록하기.
	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::TEST, Music::eSoundChannel::BGM);
}

void PlayScene::EndScene()
{

}

void PlayScene::PlayerUpdate(const double deltaTime)
{
	//comboDuration++
	_player->AddComboElapsedTime(deltaTime);

	//Set to combo 0 every ComboDuration second
	if (_player->GetComboElapsedTime() >= _player->GetComboDuration())
	{
		_player->SetCombo(0);
		_player->AddComboElapsedTime(-1);
	}
	//if getkey Down, MoveDown.
	if (Input::inputManager->IsTurnDn(VK_DOWN))
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY() + 1, _player->GetPositionX(),
			VK_DOWN, _countWallPop,deltaTime);
	}
	//if getkey Left and it's in the play screen and if brick type is not NONE, MoveLeft
	if (Input::inputManager->IsTurnDn(VK_LEFT)
		&& _player->GetPositionX() > 0
		&& _walls->GetBrick(_player->GetPositionY(), _player->GetPositionX() - 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() - 1,
			VK_LEFT, _countWallPop,deltaTime);
	}
	//if getkey Right and it's in the play screen and if brick type is not NONE, MoveRight
	if (Input::inputManager->IsTurnDn(VK_RIGHT)
		&& _player->GetPositionX() < 4
		&& _walls->GetBrick(_player->GetPositionY(), _player->GetPositionX() + 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() + 1,
			VK_RIGHT, _countWallPop,deltaTime);
	}
	//if pop wall three time
	if (_countWallPop == 3)
	{
		_brickGenSystem->GenerateNextRows();
		_countWallPop = 0;
	}
	//player oxygen system
	_playerOxySystem->ReduceOxygen(deltaTime);

	//Doing Debug:
	Debug.Log(_playerOxySystem->GetAmountOfReduceOxy());
}
