#include "pch.h"
#include "LetterScene.h"


// Graphics
#include "Button.h"
#include "Container.h"
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
	_playButton = new Button(screenWidth - 600, screenHeight - 200, 300, 100, L"가자, 무스티니로!");

	// Letter Container
	_letterContainer = new Container(0, 0, screenWidth, screenHeight);

	// Background
	_comps.background = new SingleSpriteRenderable<LetterComponents>();
	
	// LeftBox Elements
	_comps._leftBox = new Container(
		100, 100, screenWidth * 0.50, screenHeight - 100
	);
	_comps.letter = new Container(0, 0, 800, 500);

	_comps.diagrams = new Container(0, 0, 800, 300);
	_comps.leftArrowDiagram = new Container();
	_comps.downArrowDiagram = new Container();
	_comps.rightArrowDiagram = new Container();

	// RightBox Elemenst
	_comps._rightBox = new Container(
		60, 100, screenWidth * 0.50, screenHeight - 100
	);
	_comps.text1 = new Container(0, 0, 800, 50);
	_comps.blessingsOfGod = new Container(0, 0, 800, 600);
	_comps.firstBlessingOfGod = new Container(0, 0, 800, 200);
	_comps.secondBlessingOfGod = new Container(0, 0, 800, 200);
	_comps.thirdBlessingOfGod = new Container(0, 0, 800, 200);
	_comps.text2 = new Container(0, 0, 800, 50);

/********** Load Sprites **********/

	// Letter Scene Sprite Bindings
	_comps.background->BindSprite(
		ResourceManager::Get().GetImage(L"letter_background")
	);
	_comps.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"letter_background")
	);
	_comps.leftArrowDiagram->SetSizeFitImage(true);
	_comps.leftArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"left_arrow_diagram")
	);
	_comps.downArrowDiagram->SetSizeFitImage(true);
	_comps.downArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"down_arrow_diagram")
	);
	_comps.rightArrowDiagram->SetSizeFitImage(true);
	_comps.rightArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"right_arrow_diagram")
	);
	
	// Other Sprite Bindings
	
/********** Set UI Component Properties **********/

	// Buttons
	_playButton->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_playButton->SetFont(48, FontStyleBold);
	_playButton->SetTextPosition(50, 50);
	_playButton->SetRotationPivot(
		_playButton->GetCenterX(), 
		_playButton->GetCenterY()
	);
	_playButton->Rotate(-20);
	_playButton->AddEventLister("mouseClick", []() {
		_sceneManager->ChangeScene("Play");
	});

	//// Left Box Components
	// TODO: Need a script file seperate.
	// letter scripts
	_comps.letter->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_comps.letter->SetText(
		L"자랑스러운 라자브 가문의 장녀 라자냐 33세여,\n"
		L"폭탄산 무크티니로 가거라.\n\n"

		L"라자냐의 여전사로서 누구보다 폭탄산 무크티니를 깊게 파\n"
		L"라자브 가문의 전설이 되거라\n\n"

		L"학교를 안 가는걸 명예로 여겨온\n"
		L"라자브 가문의 여자답게 글을 모르겠지.\n"
		L"그림으로 설명하마.");
	_comps.letter->SetFont(24, FontStyleBold);
	// diagrams
	_comps.diagrams->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	// diagrams flexbox settings
	_comps.diagrams->SetDisplay(Display::FLEX);
	_comps.diagrams->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_comps.diagrams->SetFlexJustifyContent(FlexJustifyContent::SPACE_EVENLY);
	
	//// Right Box Components
	// text1
	_comps.text1->SetFont(24, FontStyleBold);
	_comps.text1->SetText(L"아, 그리고 니 신의 축복이 뭐였지?");
	// blessings of God
	_comps.blessingsOfGod->SetDisplay(Display::BLOCK);
	// first blessing

	// second blessing

	// third blessing

	// text2
	_comps.text2->SetFont(24, FontStyleBold);
	_comps.text2->SetText(L"별 탈 없겠지. 건투를 빈다.");

	// UI Container property
	_letterContainer->SetDisplay(Display::INLINE);

/********** Build UI Hierarchy **********/

	// Button Registration
	_buttonEventHandler->AddButton(_playButton);

	// Diagrams
	_comps.diagrams->AddChildComponent(
		_comps.leftArrowDiagram
	);
	_comps.diagrams->AddChildComponent(
		_comps.downArrowDiagram
	);
	_comps.diagrams->AddChildComponent(
		_comps.rightArrowDiagram
	);

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
	_comps.leftArrowDiagram->EnableBorder(true);
	_comps.leftArrowDiagram->SetBorder(255, 0, 0);
	_comps.downArrowDiagram->EnableBorder(true);
	_comps.downArrowDiagram->SetBorder(255, 0, 0);
	_comps.rightArrowDiagram->EnableBorder(true);
	_comps.rightArrowDiagram->SetBorder(255, 0, 0);
#endif // !NDEBUG

	// Attach blessings
	_comps.blessingsOfGod->AddChildComponent(_comps.firstBlessingOfGod);
	_comps.blessingsOfGod->AddChildComponent(_comps.secondBlessingOfGod);
	_comps.blessingsOfGod->AddChildComponent(_comps.thirdBlessingOfGod);

	// Attach right box contents to the right box
	_comps._rightBox->AddChildComponent(_comps.text1);
	_comps._rightBox->AddChildComponent(_comps.blessingsOfGod);
	_comps._rightBox->AddChildComponent(_comps.text2);

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
	_comps.text2->EnableBorder(true);
	_comps.text2->SetBorder(255, 0, 0);
#endif // !NDEBUG

	// Attach both left box and right box;
	_letterContainer->AddChildComponent(_playButton);
	_letterContainer->AddChildComponent(_comps._leftBox);
	_letterContainer->AddChildComponent(_comps._rightBox);
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
}
