#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"

EntryScene::EntryScene() 
{
}

void EntryScene::Update(const double deltaTime)
{
	
}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}

void EntryScene::InitScene()
{
}

void EntryScene::EndScene()
{
}
