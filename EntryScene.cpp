#include "pch.h"
#include "EntryScene.h"
#include "SingleRenderable.h"
#include "Container.h"
#include "Button.h"

//NDEBUG
#include"DebugConsole.h"

EntryScene::EntryScene() 
{
	_buttonEventHandler = new ButtonEventHandler();

	_mainMenuContainer = new Container(0, 0, screenWidth, screenHeight);

	//title
	_mainComs.title = new Container(30, 30, 100, 100);
	_mainComs.title->SetSizeFitImage(true);
	_mainComs.title->SetImage(
		ResourceManager::Get().GetImage(L"Razanya Title")
	);
	_mainComs.title->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	//Highst honor
	_mainComs.highScore = new Container(30, 300, 100, 100);
	_mainComs.highScore->SetSizeFitImage(true);
	_mainComs.highScore->SetImage(
		ResourceManager::Get().GetImage(L"Main_Game_Honor")
	);
	_mainComs.highScore->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	//background
	_mainComs.background = new SingleSpriteRenderable<MainMenuComponents>();
	_mainComs.background->BindSprite(
		ResourceManager::Get().GetImage(L"Main_BackGround_Image")
	);
	_mainComs.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Main_BackGround_Image")
	);

	//lazanya
	_mainComs.lazanya = new Container(1200,50,600,950);
	_mainComs.lazanya->SetSizeFitImage(true);
	_mainComs.lazanya->SetImage(
		ResourceManager::Get().GetImage(L"Main_character.razanya.original.001")
	);
	;
	_mainComs.lazanya->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	//age
	_mainComs.age = new Container(500, 40, 100, 100);
	_mainComs.age->SetSizeFitImage(true);
	_mainComs.age->SetImage(
	ResourceManager::Get().GetImage(L"Age")
	);
	_mainComs.age->SetRotationPivot(
		_mainComs.age->GetCenterX(),
		_mainComs.age->GetCenterY()
	);
	_mainComs.age->Rotate(10);
	_mainComs.age->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	_mainComs.ageChildText = new Container(225, 20, 700, 300);
	_mainComs.ageChildText->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_mainComs.ageChildText->SetFontFamily(L"Her-Leeoksun");
	_mainComs.ageChildText->SetFontColor(0, 0, 0, 255);
	_mainComs.ageChildText->SetFont(150, FontStyleRegular);
	_mainComs.ageChildText->SetText(
	L"¼¼"
	);
	_mainComs.age->AddChildComponent(_mainComs.ageChildText);

	_mainComs.ageChildTextIndex = new Container(20, 5, 100, 100);
	_mainComs.ageChildTextIndex->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_mainComs.ageChildTextIndex->SetFontFamily(L"Her-Leeoksun");
	_mainComs.ageChildTextIndex->SetFontColor(255, 255, 255, 255);
	_mainComs.ageChildTextIndex->SetFont(170, FontStyleRegular);
	_mainComs.ageChildTextIndex->SetText(
		_WStringAgeIndex(testIndex).c_str()
	);
	_mainComs.age->AddChildComponent(_mainComs.ageChildTextIndex);



	//playbutton
	_mainComs.playbutton = new Button(40, 500, 300, 100);
	_mainComs.playbutton->SetSizeFitImage(true);
	_mainComs.playbutton->SetImage(
		ResourceManager::Get().GetImage(L"Main_Game_History")
	);
	_mainComs.playbutton->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_mainComs.playbutton->SetRotationPivot(
		_mainComs.playbutton->GetCenterX(),
		_mainComs.playbutton->GetCenterY()
	);
	_mainComs.playbutton->Rotate(-7);
	_mainComs.playbutton->AddEventLister("mouseClick", [this]() {
		Music::soundManager->PlayMusic(Music::eSoundList::PaperTeraing, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Letter");
		});

	_buttonEventHandler->AddButton(_mainComs.playbutton);


	//decorator button
	_mainComs.decoratorButton = new Button(50, 700, 300, 100);
	_mainComs.decoratorButton->SetSizeFitImage(true);
	_mainComs.decoratorButton->SetImage(
		ResourceManager::Get().GetImage(L"Main_Game_Character_Select")
	);
	_mainComs.decoratorButton->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_mainComs.decoratorButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(Music::eSoundList::Button, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Decorator");
		});

	_buttonEventHandler->AddButton(_mainComs.decoratorButton);


	//Developer button
	_mainComs.developerButton = new Button(1600,20, 300, 100);
	_mainComs.developerButton->SetSizeFitImage(true);
	_mainComs.developerButton->SetImage(
		ResourceManager::Get().GetImage(L"Main_Game_Developer")
	);
	_mainComs.developerButton->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_mainComs.developerButton->AddEventLister("mouseClick", [this]() {
		Music::soundManager->PlayMusic(Music::eSoundList::Button, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Developer");
		});

	_buttonEventHandler->AddButton(_mainComs.developerButton);


	//ArtWork Button
	_mainComs.artWorkButton = new Button(1600, 100, 300, 100);
	_mainComs.artWorkButton->SetSizeFitImage(true);
	_mainComs.artWorkButton->SetImage(
		ResourceManager::Get().GetImage(L"Main_Game_Artwork")
	);
	_mainComs.artWorkButton->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_mainComs.artWorkButton->AddEventLister("mouseClick", [this]() {
		Music::soundManager->PlayMusic(Music::eSoundList::Button, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("ArtWork");
		});

	_buttonEventHandler->AddButton(_mainComs.artWorkButton);
	
	//Attach Child Component
	_mainMenuContainer->AddChildComponent(_mainComs.title);
	_mainMenuContainer->AddChildComponent(_mainComs.lazanya);
	_mainMenuContainer->AddChildComponent(_mainComs.playbutton);
	_mainMenuContainer->AddChildComponent(_mainComs.decoratorButton);
	_mainMenuContainer->AddChildComponent(_mainComs.developerButton);
	_mainMenuContainer->AddChildComponent(_mainComs.artWorkButton);
	_mainMenuContainer->AddChildComponent(_mainComs.highScore);
	_mainMenuContainer->AddChildComponent(_mainComs.age);


	//NDEBUG
#ifndef NDEBUG
	_mainComs.decoratorButton->EnableBorder(true);
	_mainComs.decoratorButton->SetBorder(0, 255, 0);
	_mainComs.playbutton->EnableBorder(true);
	_mainComs.playbutton->SetBorder(0, 255, 0);
	_mainComs.developerButton->EnableBorder(true);
	_mainComs.developerButton->SetBorder(0, 255, 0);
	_mainComs.artWorkButton->EnableBorder(true);
	_mainComs.artWorkButton->SetBorder(0, 255, 0);
#endif // NDEBUG

}

void EntryScene::Update(const double deltaTime)
{
	_buttonEventHandler->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);

	if (Input::inputManager->IsTurnDn(VK_SPACE))
	{
		testIndex++;
		_mainComs.ageChildTextIndex->SetText(
			_WStringAgeIndex(testIndex).c_str()
		);
	}


}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}

void EntryScene::InitScene()
{
	_renderSystem->RegisterRenderableObject(_mainComs.background);
	_renderSystem->RegisterRenderableObject(_mainMenuContainer);
	
	if (!playBGM) {
		Music::soundManager->PlayMusic(Music::eSoundList::background01, Music::eSoundChannel::BGM);
		playBGM = true;
	}
	
}

void EntryScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}

