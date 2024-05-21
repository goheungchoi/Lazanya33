#include "pch.h"
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
	_playButton = new Button(1080, 660, 515, 210);

	// Letter Container
	_letterContainer = new Container(0, 0, screenWidth, screenHeight);

	// Background
	_comps.background = new SingleSpriteRenderable<LetterComponents>();
	
	// LeftBox Elements
	_comps._leftBox = new Container(
		340, 185, screenWidth * 0.55, screenHeight
	);
	_comps.letter = new Container(0, 0, 700, 300);

	_comps.diagrams = new Container(0, 100, 700, 300);

	// RightBox Elemenst
	_comps._rightBox = new Container(
		20, 100, screenWidth * 0.45, screenHeight - 100
	);
	_comps.text1 = new Container(0, 0, 550, 50);
	_comps.blessingsOfGod = new Container(0, 0, 550, 500);
	_comps.blessingStateController = new BlessingsOfGodStateController();
	_comps.firstBlessingOfGod = new BlessingContainer(1078, 160, 550, 150);
	_comps.secondBlessingOfGod = new BlessingContainer(1078, 330, 550, 150);
	_comps.thirdBlessingOfGod = new BlessingContainer(1078, 500, 550, 150);

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
	_playButton->AddEventLister("mouseClick", []() {
		Music::soundManager->PlayMusic(
			Music::eSoundList::Button, Music::eSoundChannel::Effect
		);
		_sceneManager->ChangeScene("Play");
	});

	//// Left Box Components
	// TODO: Need a script file seperate.
	// letter scripts
	_comps.letter->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_comps.letter->SetFontFamily(L"경기천년바탕 Bold");
	_comps.letter->SetText(
		L"자랑스러운 라자브 가문의 장녀\n" L"라자냐 33세여, "
		L"폭탄산 무크티니로 가거라.\n\n"

		L"누구보다 폭탄산 무크티니를 깊게 파\n"
		L"라자브 가문의 영광이 되거라\n\n"

		L"학교를 안 가는걸 명예로 여겨온\n"
		L"라자브 가문의 후손답게 글을 모르겠지.\n"
		L"그림으로 설명하마.");
	_comps.letter->SetFont(36, FontStyleBold);
	// diagrams
	_comps.diagrams->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	// diagrams flexbox settings
	_comps.diagrams->SetDisplay(Display::FLEX);
	_comps.diagrams->SetFlexAlignItem(FlexAlignItem::FLEX_START);
	_comps.diagrams->SetFlexJustifyContent(FlexJustifyContent::SPACE_EVENLY);
	
	//// Right Box Components
	// text1
	_comps.text1->SetFontFamily(L"경기천년바탕 Bold");
	_comps.text1->SetFont(36, FontStyleBold);
	_comps.text1->SetText(L"아, 그리고 너 가족력이 뭐였지?");
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

#ifndef NDEBUG	// _leftBox debugging borders
	_comps._leftBox->EnableBorder(true);
	_comps._leftBox->SetBorder(255, 0, 0);
	_comps.letter->EnableBorder(true);
	_comps.letter->SetBorder(255, 0, 0);
	_comps.diagrams->EnableBorder(true);
	_comps.diagrams->SetBorder(255, 0, 0);
#endif // !NDEBUG

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
	_comps._rightBox->AddChildComponent(_comps.blessingsOfGod);

#ifndef NDEBUG	// _rightbox debugging borders
	_comps._rightBox->EnableBorder(true);
	_comps._rightBox->SetBorder(255, 0, 0);
	_comps.text1->EnableBorder(true);
	_comps.text1->SetBorder(255, 0, 0);
	_comps.blessingsOfGod->EnableBorder(true);
	_comps.blessingsOfGod->SetBorder(255, 0, 0);
	_comps.firstBlessingOfGod->EnableBorder(true);
	_comps.firstBlessingOfGod->SetBorder(0, 255, 0);
	_comps.secondBlessingOfGod->EnableBorder(true);
	_comps.secondBlessingOfGod->SetBorder(0, 255, 255);
	_comps.thirdBlessingOfGod->EnableBorder(true);
	_comps.thirdBlessingOfGod->SetBorder(0, 0, 255);
	_playButton->EnableBorder(true);
	_playButton->SetBorder(0, 255, 0);
#endif // !NDEBUG

	// Attach both left box and right box;
	_letterContainer->AddChildComponent(_comps._leftBox);
	_letterContainer->AddChildComponent(_comps._rightBox);
	_letterContainer->AddChildComponent(_playButton);
}


void LetterScene::Update(double dt)
{
	
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

	_comps.blessingStateController->UpdateContainerState();

	_comps.firstBlessingOfGod->Update(dt);
	_comps.secondBlessingOfGod->Update(dt);
	_comps.thirdBlessingOfGod->Update(dt);
}

void LetterScene::Draw()
{
	_renderSystem->Render();
}

void LetterScene::InitScene() {
	
	_renderSystem->RegisterRenderableObject(_comps.background);
	_renderSystem->RegisterRenderableObject(_letterContainer);
}

void LetterScene::EndScene() {
	_renderSystem->ClearRenderableRegistry();
	Music::soundManager->StopMusic(Music::eSoundChannel::BGM);
	
}
