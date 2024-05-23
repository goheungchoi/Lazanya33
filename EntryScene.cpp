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
		ResourceManager::Get().GetImage(L"Main_Title")
	);
	_mainComs.title->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	//Highst honor
	_mainComs.highScoreTag = new Container(30, 300, 500, 100);
	_mainComs.highScoreTag->SetSizeFitImage(true);
	_mainComs.highScoreTag->SetImage(
		ResourceManager::Get().GetImage(L"Main_Game_Honor")
	);
	_mainComs.highScoreTag->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	
	//highscore name
	_mainComs.highScoreName= new Container(100, 380, 500, 100);
	_mainComs.highScoreName->SetText(__WStringifyLetterText().c_str());
	_mainComs.highScoreName->SetFontFamily(L"°¡ÆòÇÑ¼®ºÀ Å«º× B");
	_mainComs.highScoreName->SetFont(35, FontStyleBold);
	_mainComs.highScoreName->SetFontColor(230, 35, 38);
	_mainComs.highScoreName->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	
	// Background Sunrays

	// Background Corona
	_mainComs.backgroundCorona = new Container(0, 0, 1990, 1080);

	//background
	_mainComs.background = new SingleSpriteRenderable<MainMenuComponents>();
	_mainComs.background->BindSprite(
		ResourceManager::Get().GetImage(L"Main_BackGround_Image")
	);
	_mainComs.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Main_BackGround_Image")
	);

	//lazanya
	std::wstring entryRazanyaImageName{};
	_mainComs.lazanya = new Container(1200,150,600,950);
	_mainComs.lazanya->SetSizeFitImage(true);
	_mainComs.lazanya->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	//age
	_mainComs.age = new Container(500, 70,400,200);
	_mainComs.age->SetRotationPivot(
		_mainComs.age->GetCenterX(),
		_mainComs.age->GetCenterY()
	);
	_mainComs.age->Rotate(10);
	_mainComs.age->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_mainComs.age->SetFontFamily(L"Her-Leeoksun");
	_mainComs.age->SetFontColor(233, 233, 233, 255);
	_mainComs.age->SetFont(150 , FontStyleRegular);
	
	
	
	//highscoreName
	

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
		_sceneManager->ChangeScene("ArtWork1");
		});

	_buttonEventHandler->AddButton(_mainComs.artWorkButton);
	
	//Attach Child Component
	_mainMenuContainer->AddChildComponent(_mainComs.title);
	_mainMenuContainer->AddChildComponent(_mainComs.lazanya);
	_mainMenuContainer->AddChildComponent(_mainComs.playbutton);
	_mainMenuContainer->AddChildComponent(_mainComs.decoratorButton);
	_mainMenuContainer->AddChildComponent(_mainComs.developerButton);
	_mainMenuContainer->AddChildComponent(_mainComs.artWorkButton);
	_mainMenuContainer->AddChildComponent(_mainComs.highScoreTag);
	_mainMenuContainer->AddChildComponent(_mainComs.age);
	_mainMenuContainer->AddChildComponent(_mainComs.highScoreName);

}

void EntryScene::Update(const double deltaTime)
{
	_buttonEventHandler->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
}
 
void EntryScene::Draw()
{
	_renderSystem->Render();
}

void EntryScene::InitScene()
{
	_mainComs.lazanya->SetImage(
		ResourceManager::Get().GetImage(
			L"entry_razanya_" + 
			std::to_wstring(GetGameDataHub().GetCurrentGeneration() % 3)
		)
	);
	_mainComs.age->SetText(
		_WStringAgeIndex(GetGameDataHub().GetCurrentGeneration()).c_str()
	);
	_mainComs.highScoreName->SetText(__WStringifyLetterText().c_str());
	_renderSystem->RegisterRenderableObject(_mainComs.background);
	_renderSystem->RegisterRenderableObject(_mainMenuContainer);
	
	
	Music::soundManager->PlayMusic(Music::eSoundList::background01, Music::eSoundChannel::BGM);
}

void EntryScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}

