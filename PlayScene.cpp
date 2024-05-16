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
	if (/*!�������� �����ߴ°�?*/)
	{
		//TODO: ������ ���� ������ ������Ʈ.

		_renderSystem->ClearRenderableRegistry();
		
		//���� ���۽� �ʿ���renderer���
		_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(player));
	}
	else//�������� ����ٸ�
	{
		/*player=new Decorators*/
		//TODO: ���� ���� ������Ʈ
	}
#endif
	//TODO: �������.->�÷��̾�� �긯�� �簢������ �������ؼ� ���� ���� �۵��ϴ��� Ȯ��.
	/*
	* �긯�� 3ĭ ���� �ö󰡸� ���� �������ֱ�.
	* player�� ��ĭ ������ �� ���� �긯 ��ĭ�� �ø���
	* �긯�� ȭ�� ������ ������ popfront�ϱ�
	*/
}

void PlayScene::Draw()
{
	_renderSystem->Render();
#ifdef PLAYSCENE
	if (/*!�������� �����ߴ°�?*/)
	{

		_renderSystem->Render();
		//TODO: ������ ���� ������ ������Ʈ.
	}
	else//�������� ����ٸ�
	{
		_renderSystem->Render();
		//TODO: ���� ���� ����
	}
#endif
}

void PlayScene::InitScene()
{
	_player->SetPosition(2, 4);
	_brickGenSystem->BrickGenInit();
	//������ ���� ������ �ʿ��� RenderableObject ����ϱ�.
	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::TEST, Music::eSoundChannel::BGM);
}

void PlayScene::EndScene()
{
}
