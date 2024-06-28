#include "pch.h"
#include "DescriptionScene.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

DescriptionScene::DescriptionScene()
{
	_buttonEventHandle = new ButtonEventHandler;
	_descriptionContainer = new Container(0, 0, screenWidth, screenHeight);
	
	//background
	_descriptionComps.background = new SingleSpriteRenderable<DescriptionComponents>;
	_descriptionComps.background->BindSprite(
		ResourceManager::Get().GetImage(L"Manual_BackGround")
	);
	_descriptionComps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Manual_BackGround")
	);


	//goto entrybutton
	_descriptionComps.entryButton = new Button(30, 830, 150, 200);
	_descriptionComps.entryButton->SetSizeFitImage(true);
	_descriptionComps.entryButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_descriptionComps.entryButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_descriptionComps.entryButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Entry");
		});
	_buttonEventHandle->AddButton(_descriptionComps.entryButton);

	_descriptionContainer->AddChildComponent(_descriptionComps.entryButton);
}

void DescriptionScene::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}

void DescriptionScene::Draw()
{
	_renderSystem->Render();
}

void DescriptionScene::InitScene()
{
	_renderSystem->RegisterRenderableObject(_descriptionComps.background);
	_renderSystem->RegisterRenderableObject(_descriptionContainer);
}

void DescriptionScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}
