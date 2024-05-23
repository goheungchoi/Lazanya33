#include "pch.h"
#include "ArtWorkScene2.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

ArtWorkScene2::ArtWorkScene2()
{
	_buttonEventHandle = new ButtonEventHandler();
	_artWork2Container = new Container(0, 0, screenWidth, screenHeight);
	//background
	_artWork2Comps.background = new SingleSpriteRenderable<ArtWork2Components>();
	_artWork2Comps.background->BindSprite(
		ResourceManager::Get().GetImage(L"artwork02_Park")
	);
	_artWork2Comps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"artwork02_Park")
	);

	//prevbutton
	_artWork2Comps.prevButton = new Button(30, 830, 150, 200);
	_artWork2Comps.prevButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_artWork2Comps.prevButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_artWork2Comps.prevButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("ArtWork1");
		});
	_buttonEventHandle->AddButton(_artWork2Comps.prevButton);

	//nextbutton
	_artWork2Comps.nextButton = new Button(1740, 830, 150, 200);
	_artWork2Comps.nextButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_frontButton")
	);
	_artWork2Comps.nextButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_artWork2Comps.nextButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("ArtWork3");
		});
	_buttonEventHandle->AddButton(_artWork2Comps.nextButton);
	//attach child component
	_artWork2Container->AddChildComponent(_artWork2Comps.prevButton);
	_artWork2Container->AddChildComponent(_artWork2Comps.nextButton);
}

void ArtWorkScene2::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}

void ArtWorkScene2::Draw()
{
	_renderSystem->Render();
}

void ArtWorkScene2::InitScene()
{
	_renderSystem->RegisterRenderableObject(_artWork2Comps.background);
	_renderSystem->RegisterRenderableObject(_artWork2Container);
}

void ArtWorkScene2::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}
