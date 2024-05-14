#include "pch.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
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
}

void PlayScene::Draw()
{
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
