#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"

EntryScene::EntryScene() 
{
	_renderSystem->RegisterRenderableObject(player);
}

void EntryScene::Update(double DeltaTime)
{
}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}
