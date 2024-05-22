﻿#include "pch.h"
#include "LetterScene.h"
#include "EntryScene.h"
#include "DebugConsole.h"

// Graphics
#include "Button.h"
#include "Container.h"
#include "BlessingContainer.h"
#include "SingleRenderable.h"

// Resource
#include "ResourceManager.h"

LetterScene::LetterScene() {
	
	__InitComponents();
	
	
}

LetterScene::~LetterScene() {

}

void LetterScene::__InitComponents() {

/********** Allocate Memory **********/
	// Button Handler
	_buttonEventHandler = new ButtonEventHandler();

	// Button
	_playButton = new Button(1110, 764, 468, 100);
	// Letter Container
	_letterContainer = new Container(0, 0, screenWidth, screenHeight);

	// Background
	_comps.background = new SingleSpriteRenderable<LetterComponents>();
	
	// LeftBox Elements
	_comps._leftBox = new Container(
		340, 185, screenWidth * 0.55, screenHeight
	);
	_comps.letter = new Container(350, 200, 700, 500);

	_comps.diagrams = new Container(350, 600, 700, 300);

	// RightBox Elemenst
	_comps._rightBox = new Container(
		20, 100, screenWidth * 0.45, screenHeight - 100
	);
	_comps.text1 = new Container(1060, 120, 600, 50);
	_comps.runningInFamily = new Container(1150, 120, 144, 50);
	_comps.blessingsOfGod = new Container(0, 0, 550, 500);
	_comps.blessingStateController = new BlessingsOfGodStateController();
	_comps.firstBlessingOfGod = new BlessingContainer(1078, 180, 550, 150);
	_comps.secondBlessingOfGod = new BlessingContainer(1078, 350, 550, 150);
	_comps.thirdBlessingOfGod = new BlessingContainer(1078, 520, 550, 150);

/********** Load Sprites **********/

	// Letter Scene Sprite Bindings
	_playButton->SetImage(
		ResourceManager::Get().GetImage(L"play_button")
	);
	_comps.background->BindSprite(
		ResourceManager::Get().GetImage(L"letter_background")
	);
	_comps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"letter_background")
	);
	_comps.diagrams->SetImage(
		ResourceManager::Get().GetImage(L"tutorial_diagram")
	);
	
	// Other Sprite Bindings
	
/********** Set UI Component Properties **********/

	// Buttons
	_playButton->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_playButton->SetImageStrecth(false);
	_playButton->SetImageAlignment(H_DIRECTION::CENTER, V_DIRECTION::CENTER);
	
	_playButton->AddEventLister("mouseEnter", [this]() {
		_playButton->SetImageIntensity(2.0f);
	});
	_playButton->AddEventLister("mouseLeave", [this]() {
		_playButton->SetImageIntensity(1/2.0f);
	});
	_playButton->AddEventLister("mouseClick", [this]() {
		if (isBlessingSelected)
		{
			Music::soundManager->PlayMusic(
				Music::eSoundList::Button, Music::eSoundChannel::Effect
			);
			GetGameDataHub().SetCurrentUserBlessIndex(
				static_cast<int>(
					_comps.blessingStateController->GetCurrentSelectedBlessingType()
					)
			);
			_sceneManager->ChangeScene("Play");
		}
	});

	//// Left Box Components
	// TODO: Need a script file seperate.
	// letter scripts 한글
	_comps.letter->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_comps.letter->SetFontFamily(L"그녀-이옥선");
	_comps.letter->SetText(__WStringifyLetterText().c_str());
	_comps.letter->SetFont(36, FontStyleBold);
	// diagrams
	_comps.diagrams->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	// diagrams flexbox settings
	_comps.diagrams->SetDisplay(Display::FLEX);
	_comps.diagrams->SetFlexAlignItem(FlexAlignItem::FLEX_START);
	_comps.diagrams->SetFlexJustifyContent(FlexJustifyContent::SPACE_EVENLY);
	int a;
	//// Right Box Components
	// text1
	_comps.text1->SetFontFamily(L"GyeonggiBatang Bold");
	_comps.text1->SetFont(36, FontStyleBold);
	_comps.text1->SetText(L"3개의             중 하나를 선택해 진행.");
	// running In Family
	_comps.runningInFamily->SetFontFamily(L"GyeonggiBatang Bold");
	_comps.runningInFamily->SetFont(38, FontStyleBold);
	_comps.runningInFamily->SetFontColor(181, 0, 0);
	_comps.runningInFamily->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_comps.runningInFamily->SetText(L"'가족력'");

	// blessings of God
	_comps.blessingsOfGod->SetDisplay(Display::BLOCK);
	// first blessingS
	_comps.firstBlessingOfGod->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_comps.secondBlessingOfGod->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_comps.thirdBlessingOfGod->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);

	// UI Container property
	_letterContainer->SetDisplay(Display::INLINE);

/********** Build UI Hierarchy **********/

	// Button Registration
	_buttonEventHandler->AddButton(_playButton);

	// Diagrams
	_comps.diagrams->SetSizeFitImage(true);

	// Attach letter to the left box
	_comps._leftBox->AddChildComponent(_comps.letter);
	// Attach diagrams to the left box
	_comps._leftBox->AddChildComponent(_comps.diagrams);

	// Attach blessings
	_comps.blessingsOfGod->AddChildComponent(_comps.firstBlessingOfGod);
	_comps.blessingsOfGod->AddChildComponent(_comps.secondBlessingOfGod);
	_comps.blessingsOfGod->AddChildComponent(_comps.thirdBlessingOfGod);

	// Blessing State Controller
	_comps.blessingStateController->AddBlessingContainer(_comps.firstBlessingOfGod);
	_comps.blessingStateController->AddBlessingContainer(_comps.secondBlessingOfGod);
	_comps.blessingStateController->AddBlessingContainer(_comps.thirdBlessingOfGod);

	// Attach right box contents to the right box
	_comps._rightBox->AddChildComponent(_comps.text1);
	_comps._rightBox->AddChildComponent(_comps.runningInFamily);
	_comps._rightBox->AddChildComponent(_comps.blessingsOfGod);


	// Attach both left box and right box;
	_letterContainer->AddChildComponent(_comps._leftBox);
	_letterContainer->AddChildComponent(_comps._rightBox);
	_letterContainer->AddChildComponent(_playButton);
}


void LetterScene::Update(double dt)
{
	_playButton->SetActive(isBlessingSelected);
	// Check the mouse button events
	
	_buttonEventHandler->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);
	
	_comps.blessingStateController->HandleMouseEvent(
		Input::inputManager->GetMouseClient().x,
		Input::inputManager->GetMouseClient().y,
		Input::inputManager->IsCurrDn(VK_LBUTTON),
		Input::inputManager->IsCurrUp(VK_LBUTTON)
	);

	_comps.blessingStateController->UpdateContainerState(isBlessingSelected);

	_comps.firstBlessingOfGod->Update(dt);
	_comps.secondBlessingOfGod->Update(dt);
	_comps.thirdBlessingOfGod->Update(dt);
}

void LetterScene::Draw()
{
	_renderSystem->Render();
}

void LetterScene::InitScene() {
	_playButton->SetActive(false);
	_comps.firstBlessingOfGod->Init();
	_comps.secondBlessingOfGod->Init();
	_comps.thirdBlessingOfGod->Init();
	_renderSystem->RegisterRenderableObject(_comps.background);
	_renderSystem->RegisterRenderableObject(_letterContainer);
}

void LetterScene::EndScene() {
	_renderSystem->ClearRenderableRegistry();
	Music::soundManager->StopMusic(Music::eSoundChannel::BGM);
	_comps.firstBlessingOfGod->Reset();
	_comps.secondBlessingOfGod->Reset();
	_comps.thirdBlessingOfGod->Reset();
	_comps.blessingStateController->Reset();
}
