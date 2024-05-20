#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

//NDEBUG
#include"DebugConsole.h"

EntryScene::EntryScene() 
{
	_mainMenuContainer=new Container(0, 0, screenWidth, screenHeight);
	_mainMenuComponents.background = new SingleSpriteRenderable<MainMenuComponents>();
	_mainMenuComponents.background->BindSprite(
		ResourceManager::Get().GetImage(L"mainmenu.background.001")
	);
	_mainMenuComponents.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"mainmenu.background.001")
	);


	_mainMenuComponents.lazanya = new Container(1200,50,600,950);
	_mainMenuComponents.lazanya->SetSizeFitImage(true);
	_mainMenuComponents.lazanya->SetImage(
		ResourceManager::Get().GetImage(L"Main_character.razanya.original.001")
	);
	;


	button = new Button(100, 500, 300, 100, L"유서 읽기");
	
}

void EntryScene::Update(const double deltaTime)
{
	if (button->HitTest(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y)
		&&
		Input::inputManager->IsTurnDn(VK_LBUTTON)
		)
	{
		//button-> image change
		Music::soundManager->PlayMusic(Music::eSoundList::Button, Music::eSoundChannel::Effect);
	}
	if (button->HitTest(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y)
		&&
		Input::inputManager->IsTurnUp(VK_LBUTTON)
		
		)
	{
		
	}

	
}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}

void EntryScene::InitScene()
{
	_renderSystem->RegisterRenderableObject(_mainMenuComponents.background);
	_renderSystem->RegisterRenderableObject(button);
	_renderSystem->RegisterRenderableObject(_mainMenuComponents.lazanya);
	Music::soundManager->PlayMusic(Music::eSoundList::background01, Music::eSoundChannel::BGM);
}

void EntryScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}

void EntryScene::GoToGameScene()
{
	//게임씬으로가는로직.
	_sceneManager->ChangeScene("Play");
}
