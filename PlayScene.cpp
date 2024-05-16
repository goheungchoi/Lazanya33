#include "pch.h"
#include "PlayScene.h"
#include "BrickGenerationSystem.h"
#include "PlayerBricksInteractionSystem.h"

#include "GridMap.h"
#include "Player.h"
#include "Wall.h"

PlayScene::PlayScene() 
: _gridMap{new GridMap(
		GRID_MAP_POSITION_X, 
		GRID_MAP_POSITION_Y, 
		wallNumRows, wallNumCols, 120, 120)}, 
	_player{new Player()}, 
	_walls{new Wall()},
	_brickGenSystem{new BrickGenSystem(_walls)}, 
	_playerBrickInteractionSystem{
		new PlayerBricksInteractionSystem(_player,_walls)
	}
{	
	_gridMap->AttachChildRenderable(_walls);
	_gridMap->AttachChildRenderable(_player);
	_renderSystem->RegisterRenderableObject(_gridMap);
}

void PlayScene::Update(double DeltaTime)
{
	//if Didn't init, init one time
	if (!DidInit)
	{
		InitScene();
		DidInit = true;
	}
	//for test, if turn down space, gen brick

	//if getkey Down, MoveDown.
	if (Input::inputManager->IsTurnDn(VK_DOWN))
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY() + 1,_player->GetPositionX(),
			VK_DOWN,_countWallPop);
		
	} 
	//if getkey Left and it's in the play screen and if brick type is not NONE, MoveLeft
	if (Input::inputManager->IsTurnDn(VK_LEFT)
		&&_player->GetPositionX() > 0
		&& _walls->GetBrick(_player->GetPositionY(), _player->GetPositionX() - 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() - 1,
			VK_LEFT, _countWallPop);
	}
	//if getkey Right and it's in the play screen and if brick type is not NONE, MoveRight
	if (Input::inputManager->IsTurnDn(VK_RIGHT)
		&&_player->GetPositionX() < 4
		&& _walls->GetBrick(_player->GetPositionY(), _player->GetPositionX() + 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() + 1,
			VK_RIGHT, _countWallPop);
	}
	//if pop wall three time
	if (_countWallPop==3)
	{
		_brickGenSystem->GenerateNextRows();
		_countWallPop = 0;
	}
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
	//TODO: 데모버젼.->플레이어와 브릭만 사각형으로 렌더링해서 게임 로직 작동하는지 확인.
	/*
	* 브릭이 3칸 위로 올라가면 새로 생성해주기.
	* player가 한칸 내려갈 때 마다 브릭 한칸씩 올리기
	* 브릭이 화면 밖으로 나가면 popfront하기
	*/
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
