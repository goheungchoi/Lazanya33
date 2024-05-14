#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"

EntryScene::EntryScene() {
	_drawableObject = new SingleRenderable<int>(100, 100);
}

void EntryScene::Update(double DeltaTime)
{
	 _sceneManager.ChangeScene(_sceneDependencies.find("Letter")->second);
}
 
void EntryScene::Draw()
{
}
