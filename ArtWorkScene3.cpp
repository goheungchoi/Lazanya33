#include "pch.h"
#include "ArtWorkScene3.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

ArtWorkScene3::ArtWorkScene3()
{
	_buttonEventHandle = new ButtonEventHandler();
	_artWork3Container = new Container(0, 0, screenWidth, screenHeight);
	//background
	_artWork3Comps.background = new SingleSpriteRenderable<ArtWork3Components>();
	_artWork3Comps.background->BindSprite(
		ResourceManager::Get().GetImage(L"Artwork3_Choi")
	);
	_artWork3Comps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Artwork3_Choi")
	);

	//prevbutton
	_artWork3Comps.prevButton = new Button(30, 830, 150, 200);
	_artWork3Comps.prevButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_artWork3Comps.prevButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_artWork3Comps.prevButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("ArtWork2");
		});
	_buttonEventHandle->AddButton(_artWork3Comps.prevButton);

	//attach child component
	_artWork3Container->AddChildComponent(_artWork3Comps.prevButton);

}

void ArtWorkScene3::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}

void ArtWorkScene3:: Draw()
{
	_renderSystem->Render();
}

void ArtWorkScene3::InitScene()
{
	_renderSystem->RegisterRenderableObject(_artWork3Comps.background);
	_renderSystem->RegisterRenderableObject(_artWork3Container);
}

void ArtWorkScene3::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}
