#include "pch.h"
#include "LetterScene.h"

#include "DebugConsole.h"

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
	_playButton = new Button(
		1080, 660, 
		515, 210, 
		L"����Ƽ�Ϸ�!");

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
	_comps.leftArrowDiagram = new Container();
	_comps.downArrowDiagram = new Container();
	_comps.rightArrowDiagram = new Container();

	// RightBox Elemenst
	_comps._rightBox = new Container(
		20, 100, screenWidth * 0.45, screenHeight - 100
	);
	_comps.text1 = new Container(0, 0, 550, 50);
	_comps.blessingsOfGod = new Container(0, 0, 550, 500);
	_comps.firstBlessingOfGod = new Container(0, 20, 550, 140);
	_comps.secondBlessingOfGod = new Container(0, 40, 550, 140);
	_comps.thirdBlessingOfGod = new Container(0, 60, 550, 140);

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
	_playButton->SetFontFamily(L"Segoe UI");
	_playButton->SetFont(48, FontStyleBold);
	_playButton->SetTextPosition(10, 10);
	_playButton->SetRotationPivot(
		_playButton->GetCenterX(), 
		_playButton->GetCenterY()
	);
	//_playButton->Rotate(-20);
	_playButton->AddEventLister("mouseClick", []() {
		_sceneManager->ChangeScene("Play");
	});

	//// Left Box Components
	// TODO: Need a script file seperate.
	// letter scripts
	_comps.letter->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_comps.letter->SetFontFamily(L"Segoe UI");
	_comps.letter->SetText(
		L"�ڶ������� ���ں� ������ ���\n" L"���ڳ� 33����, "
		L"��ź�� ��ũƼ�Ϸ� ���Ŷ�.\n\n"

		L"�������� ��ź�� ��ũƼ�ϸ� ��� ��\n"
		L"���ں� ������ ������ �ǰŶ�\n\n"

		L"�б��� �� ���°� ���� ���ܿ�\n"
		L"���ں� ������ �ļմ�� ���� �𸣰���.\n"
		L"�׸����� �����ϸ�.");
	_comps.letter->SetFont(24, FontStyleBold);
	// diagrams
	_comps.diagrams->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	// diagrams flexbox settings
	_comps.diagrams->SetDisplay(Display::FLEX);
	_comps.diagrams->SetFlexAlignItem(FlexAlignItem::FLEX_START);
	_comps.diagrams->SetFlexJustifyContent(FlexJustifyContent::SPACE_EVENLY);
	
	//// Right Box Components
	// text1
	_comps.text1->SetFontFamily(L"Segoe UI");
	_comps.text1->SetFont(24, FontStyleBold);
	_comps.text1->SetText(L"��, �׸��� �� �������� ������?");
	// blessings of God
	_comps.blessingsOfGod->SetDisplay(Display::BLOCK);
	// first blessing
	_comps.firstBlessingOfGod->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_comps.secondBlessingOfGod->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_comps.thirdBlessingOfGod->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	// second blessing

	// third blessing


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
