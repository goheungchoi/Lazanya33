#include "pch.h"
#include "BlcokIntroduction.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

BlcokIntroduction::BlcokIntroduction()
{
	_buttonEventHandle = new ButtonEventHandler();
	_blcokIntroContainer = new Container(0, 0, screenWidth, screenHeight);
	
	//background
	_blockIntroComps.background = new SingleSpriteRenderable<BlcokIntroductionComponents>();
	_blockIntroComps.background->BindSprite(
		ResourceManager::Get().GetImage(L"Block_Introduce copy 2")
	);
	_blockIntroComps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Block_Introduce copy 2")
	);

	//entry button
	_blockIntroComps.entryButton = new Button(30, 830, 150, 200);
	_blockIntroComps.entryButton->SetSizeFitImage(true);
	_blockIntroComps.entryButton->SetImage(
		ResourceManager::Get().GetImage(L"UI_backButton")
	);
	_blockIntroComps.entryButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_blockIntroComps.entryButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::BackSound, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Entry");
		});
	_buttonEventHandle->AddButton(_blockIntroComps.entryButton);

	//Attach Child Component
	_blcokIntroContainer->AddChildComponent(_blockIntroComps.entryButton);
}

void BlcokIntroduction::Update(double deltaTime)
{
	_buttonEventHandle->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}

void BlcokIntroduction::Draw()
{
	_renderSystem->Render();
}

void BlcokIntroduction::InitScene()
{
	_renderSystem->RegisterRenderableObject(_blockIntroComps.background);
	_renderSystem->RegisterRenderableObject(_blcokIntroContainer);
}

void BlcokIntroduction::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}
