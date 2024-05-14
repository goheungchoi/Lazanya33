#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"

EntryScene::EntryScene() {
	
}

void EntryScene::Update(double DeltaTime)
{
	
}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}
