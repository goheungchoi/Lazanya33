#include "pch.h"
#include "DeveloperScene.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

DeveloperScene::DeveloperScene()
{
	_buttonEventHandle = new ButtonEventHandler();
	_creditContainer = new Container(0, 0, screenWidth, screenHeight);
	
	//backgrond
	_creditComps.background = new SingleSpriteRenderable<CreditComponents>();
	_creditComps.background->BindSprite(
		ResourceManager::Get().GetImage(L"BG_Credit")
	);
	_creditComps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"BG_Credit")
	);

	//goto entrySceneButton
	_creditComps.entryButton = new Button(30, 830, 150, 200);
	_creditComps.entryButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_creditComps.entryButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_creditComps.entryButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Entry");
		});
	_buttonEventHandle->AddButton(_creditComps.entryButton);

	//Attach Child Component
	_creditContainer->AddChildComponent(_creditComps.entryButton);
	

}

void DeveloperScene::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}

void DeveloperScene::Draw()
{
	_renderSystem->Render();
}

void DeveloperScene::InitScene()
{
	_renderSystem->RegisterRenderableObject(_creditComps.background);
	_renderSystem->RegisterRenderableObject(_creditContainer);
}

void DeveloperScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}
