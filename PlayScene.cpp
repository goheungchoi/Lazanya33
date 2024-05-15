#include "pch.h"
#include "PlayScene.h"
#include "BrickGenerationSystem.h"
PlayScene::PlayScene()
{
	_renderSystem->RegisterRenderableObject(_walls);
	_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(_player));
	//가족력 선택 이전에 필요한 RenderableObject 등록하기.
}

void PlayScene::Update(double DeltaTime)
{
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
