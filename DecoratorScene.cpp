#include "pch.h"
#include "DecoratorScene.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

DecoratorScene::DecoratorScene()
{
	_buttonEventHandle = new ButtonEventHandler();
	_decoratorContainer = new Container(0, 0, screenWidth, screenHeight);

	//backgrond
	_decoratorComps.background = new SingleSpriteRenderable<DecoratorComponents>();
	_decoratorComps.background->BindSprite(
		ResourceManager::Get().GetImage(L"UI_darkened_backGround")
	);
	_decoratorComps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"UI_darkened_backGround")
	);

	//goto entrySceneButton
	_decoratorComps.entryButton = new Button(30, 830, 150, 200);
	_decoratorComps.entryButton->SetSizeFitImage(true);
	_decoratorComps.entryButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_decoratorComps.entryButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_decoratorComps.entryButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Entry");
		});
	_buttonEventHandle->AddButton(_decoratorComps.entryButton);

	//decorator
	_decoratorComps.decorator = new Container(245, 60, 1430, 768);
	_decoratorComps.decorator->SetSizeFitImage(true);
	_decoratorComps.decorator->SetImage(
		ResourceManager::Get().GetImage(L"UI_familyHistoryGroup")
	);
	_decoratorComps.decorator->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);


	//Attach Child Component
	_decoratorContainer->AddChildComponent(_decoratorComps.entryButton);
	_decoratorContainer->AddChildComponent(_decoratorComps.decorator);


}

void DecoratorScene::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);

}

void DecoratorScene::Draw()
{
	_renderSystem->Render();
}

void DecoratorScene::InitScene()
{
	_renderSystem->RegisterRenderableObject(_decoratorComps.background);
	_renderSystem->RegisterRenderableObject(_decoratorContainer);
}

void DecoratorScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}
