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
	_mainComs.backgroundSunrays = new Container(0, 0, 2500, 2500);
	_mainComs.backgroundSunrays->SetImage(
		ResourceManager::Get().GetImage(L"Sun_moving02")
	);
	_mainComs.backgroundSunrays->SetX((int(screenWidth - 2500) >> 1)+100);
	_mainComs.backgroundSunrays->SetY((int(screenHeight - 2500) >> 1)-100);
	_mainComs.backgroundSunrays->SetImageAlignment(H_DIRECTION::CENTER, V_DIRECTION::CENTER);
	_mainComs.backgroundSunrays->SetRotationPivot(
		_mainComs.backgroundSunrays->GetCenterX(),
		_mainComs.backgroundSunrays->GetCenterY()
	);

	// Background Corona
	_mainComs.backgroundCorona = new Container(0, 0, 829, 832);
	_mainComs.backgroundCorona->SetSizeFitImage(true);
	_mainComs.backgroundCorona->SetZValue(10);
	_mainComs.backgroundCorona->SetImage(
		ResourceManager::Get().GetImage(L"Sun_moving01")
	);
	_mainComs.backgroundCorona->SetX(((screenWidth - 830) >> 1) + 110);
	_mainComs.backgroundCorona->SetY(((screenHeight - 830) >> 1) - 30);
	_mainComs.backgroundCorona->SetRotationPivot(
		_mainComs.backgroundCorona->GetCenterX(),
		_mainComs.backgroundCorona->GetCenterY()
	);

	// Background Container
	_mainComs.backgroundContainers = new Container();
	_mainComs.backgroundContainers->AddChildComponent(_mainComs.backgroundCorona);
	_mainComs.backgroundContainers->AddChildComponent(_mainComs.backgroundSunrays);

	// Sun Flares
	Bitmap* sunFlaresSprite = ResourceManager::Get().GetImage(L"Sun_circle_fixed");
	_mainComs.SunFlares = new SingleSpriteRenderable<SunFlares>();
	_mainComs.SunFlares->BindSprite(sunFlaresSprite);
	_mainComs.SunFlares->SetPosition(
		1068,
		530
	);
	_mainComs.SunFlares->UpdateSpritePivotPosition(
		H_DIRECTION::CENTER, V_DIRECTION::CENTER
	);
	_mainComs.SunFlares->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Sun_circle_fixed")
	);

	// Sun
	Bitmap* sunSprite = ResourceManager::Get().GetImage(L"Sun_Face_fixed");
	_mainComs.Sun = new SingleSpriteRenderable<Sun>();
	_mainComs.Sun->BindSprite(sunSprite);
	_mainComs.Sun->SetPosition(
		1040,
		530
	);
	_mainComs.Sun->UpdateSpritePivotPosition(
		H_DIRECTION::CENTER, V_DIRECTION::CENTER
	);
	_mainComs.Sun->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Sun_Face_fixed")
	);

	// Temple
	_mainComs.temple = new SingleSpriteRenderable<Temple>();
	_mainComs.temple->BindSprite(
		ResourceManager::Get().GetImage(L"Cave_fixed")
	);
	_mainComs.temple->SetPosition(0, 455);
	_mainComs.temple->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"Cave_fixed")
	);

	// Background
	_mainComs.background = new SingleSpriteRenderable<MainMenuComponents>(false);
	_mainComs.background->AttachChildRenderable(_mainComs.Sun);
	_mainComs.background->AttachChildRenderable(_mainComs.SunFlares);
	_mainComs.background->AttachChildRenderable(_mainComs.temple);

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

	//block intro button
	_mainComs.blockButton = new Button(300, 700, 300, 100);
	_mainComs.blockButton->SetSizeFitImage(true);
	_mainComs.blockButton->SetImage(
		ResourceManager::Get().GetImage(L"Stone_Dictionary")
	);
	_mainComs.blockButton->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	
	_mainComs.blockButton->AddEventLister("mouseClick", [this]() {
		Music::soundManager->PlayMusic(Music::eSoundList::PaperTeraing, Music::eSoundChannel::Effect);
		_sceneManager->ChangeScene("Block");
		});

	_buttonEventHandler->AddButton(_mainComs.blockButton);
	
	//Attach Child Component
	_mainMenuContainer->AddChildComponent(_mainComs.title);
	_mainMenuContainer->AddChildComponent(_mainComs.lazanya);
	_mainMenuContainer->AddChildComponent(_mainComs.playbutton);
	_mainMenuContainer->AddChildComponent(_mainComs.decoratorButton);
	_mainMenuContainer->AddChildComponent(_mainComs.developerButton);
	_mainMenuContainer->AddChildComponent(_mainComs.artWorkButton);
	_mainMenuContainer->AddChildComponent(_mainComs.blockButton);
	_mainMenuContainer->AddChildComponent(_mainComs.highScoreTag);
	_mainMenuContainer->AddChildComponent(_mainComs.age);
	_mainMenuContainer->AddChildComponent(_mainComs.highScoreName);
}

void EntryScene::Update(const double deltaTime)
{
	_mainComs.backgroundSunrays->Rotate(deltaTime*20.0);
	_mainComs.backgroundCorona->Rotate(-deltaTime*20.0);
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
	_renderSystem->RegisterRenderableObject(_mainComs.backgroundContainers);
	_renderSystem->RegisterRenderableObject(_mainComs.background);
	_renderSystem->RegisterRenderableObject(_mainMenuContainer);
	
	
	Music::soundManager->PlayMusic(Music::eSoundList::background01, Music::eSoundChannel::BGM);
}

void EntryScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}

