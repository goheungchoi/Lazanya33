#include "pch.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(player));
}

void PlayScene::Update(double DeltaTime)
{

}

void PlayScene::Draw()
{
	_renderSystem->Render();
}
