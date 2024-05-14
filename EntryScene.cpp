#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"

EntryScene::EntryScene() {
	_drawableObject = new SingleRenderable<int>(100, 100);
}

void EntryScene::Update(double DeltaTime)
{
	if (Input::inputManager->IsTurnDn(VK_SPACE))
	{
		_sceneManager.ChangeScene(_sceneDependencies.find("Letter")->second);
	}
}
 
void EntryScene::Draw()
{
}
