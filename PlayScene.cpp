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
		15, 5, 120, 120)}, 
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
	_player->SetPosition(2, 1);
  _brickGenSystem->GenerateNextRows();
	_brickGenSystem->GenerateNextRows();
	_brickGenSystem->GenerateNextRows();
	//������ ���� ������ �ʿ��� RenderableObject ����ϱ�.
}

void PlayScene::Update(double DeltaTime)
{
	//for test, if turn down space, gen brick
	if (Input::inputManager->IsTurnDn(VK_SPACE))
	{
		_brickGenSystem->GenerateNextRows();
	}

	if (Input::inputManager->IsTurnDn(VK_DOWN))
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY()+1,_player->GetPositionX());
	}
	if (Input::inputManager->IsTurnDn(VK_LEFT))
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX()-1);
	}
	if (Input::inputManager->IsTurnDn(VK_RIGHT))
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX()+1);
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
