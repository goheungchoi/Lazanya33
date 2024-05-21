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
	_creditComs.background = new SingleSpriteRenderable<CreditComponents>();
	_creditComs.background->BindSprite(
		ResourceManager::Get().GetImage(L"BG_Credit")
	);
	_creditComs.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"BG_Credit")
	);

	//goto entrySceneButton
	_creditComs.EntryButton = new Button(40, 855, 150, 200);
	_creditComs.EntryButton->SetSizeFitImage(true);
	_creditComs.EntryButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_creditComs.EntryButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_creditComs.EntryButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Entry");
		});
	_buttonEventHandle->AddButton(_creditComs.EntryButton);

	//Attach Child Component
	_creditContainer->AddChildComponent(_creditComs.EntryButton);
	
#ifndef NDEBUG
	_creditComs.EntryButton->EnableBorder(true);
	_creditComs.EntryButton->SetBorder(0, 0, 255);
#endif
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
	_renderSystem->RegisterRenderableObject(_creditComs.background);
	_renderSystem->RegisterRenderableObject(_creditContainer);
}

void DeveloperScene::EndScene()
{
}
