#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"
#include "Player.h"

EntryScene::EntryScene() {
	Player a;
}

void EntryScene::Update(double DeltaTime)
{
	
}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}
