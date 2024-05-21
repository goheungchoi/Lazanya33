#include "pch.h"
#include "ArtWorkScene1.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

ArtWorkScene1::ArtWorkScene1()
{
	_buttonEventHandle = new ButtonEventHandler();
	_artWork1Container = new Container(0, 0, screenWidth, screenHeight);
	//background
	_artWork1Comps.background = new SingleSpriteRenderable<ArtWork1Components>();
	_artWork1Comps.background->BindSprite(
		ResourceManager::Get().GetImage(L"UI_darkened_backGround")
	);
	_artWork1Comps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"UI_darkened_backGround")
	);

	//goto entryscene button
	_artWork1Comps.entryButton = new Button(30, 830, 150, 200);
	_artWork1Comps.entryButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_artWork1Comps.entryButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_artWork1Comps.entryButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Entry");
		});
	_buttonEventHandle->AddButton(_artWork1Comps.entryButton);

	//attach child component
	_artWork1Container->AddChildComponent(_artWork1Comps.entryButton);
}

void ArtWorkScene1::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}

void ArtWorkScene1::Draw()
{
	_renderSystem->Render();
}

void ArtWorkScene1::InitScene()
{
	_renderSystem->RegisterRenderableObject(_artWork1Comps.background);
	_renderSystem->RegisterRenderableObject(_artWork1Container);
}

void ArtWorkScene1::EndScene()
{
}
