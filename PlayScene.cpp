#include "pch.h"
#include "PlayScene.h"
#include "GridMap.h"
#include "Player.h"
#include "Wall.h"
#include "Container.h"

#include "SingleRenderable.h"
#include "Animation.h"
#include "SequentialAnimationPack.h"

//decorator
#include "TenaciousDwarf.h"
#include "Wimp.h"
#include "Pummeler.h"
#include "SugarGirl.h"
#include "Anaerobic.h"
#include "Naughty.h"
#include "GoldSeeker.h"

//system
#include "BrickGenerationSystem.h"
#include "PlayerBricksInteractionSystem.h"
#include "PlayerOxygenSystem.h"

#include "ResourceManager.h"

constexpr double PLAYER_OXYGEN_REDUCE_INITAL_VALUE = 10.0;

using namespace Gdiplus;

PlayScene::PlayScene() {	
	//InitScene();


//// System Creations
//	_brickGenSystem = new BrickGenSystem(_wall);
//	_playerOxySystem = new PlayerOxygenSystem(
//		_player, PLAYER_OXYGEN_REDUCE_INITAL_VALUE
//	);
//	_playerBrickInteractionSystem = new PlayerBricksInteractionSystem(
//		_player, _wall, _playerOxySystem
//	);
//
//// RenderSystem Registration
//	_renderSystem->RegisterRenderableObject(_gridMapBackground);
//	_renderSystem->RegisterRenderableObject(_gridMap);
//	_renderSystem->RegisterRenderableObject(_gamePlayUIContainer);
//	
//
//#ifndef NDEBUG
//	// A spinning square for performance measure
//	_ui = new Container(100, 100, 100, 100);
//	_ui->SetDisplay(Display::FLEX);
//	_ui->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
//	_ui->SetFlexJustifyContent(FlexJustifyContent::FLEX_START);
//	_uiChild1 = new Container(20, 20, 20, 20);
//	_uiChild1->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
//	_uiChild2 = new Container(60, 60, 20, 20);
//	_ui->AddChildComponent(_uiChild1);
//	_ui->AddChildComponent(_uiChild2);
//	_uiChild1->EnableBorder(true);
//	_uiChild1->SetBorder(0, 255, 0);
//	_uiChild2->EnableBorder(true);
//	_uiChild2->SetBorder(0, 0, 255);
//	_ui->EnableBorder(true);
//	_ui->SetBorder(255, 0, 0);
//	_ui->SetText(L"Hello!");
//	_ui->SetRotationPivot(_ui->GetCenterX(), _ui->GetCenterY());
//
//	_fpsBox = new Container(5, 5, 100, 50);
//	_fpsBox->SetFont(24, FontStyleBold);
//	_fpsBox->SetText(StringifyFrameRate(0).c_str());
//
//	_renderSystem->RegisterRenderableObject(_ui);
//	_renderSystem->RegisterRenderableObject(_fpsBox);
//#endif
//
//// Game Play Initialization
//	_player->SetPosition(2, 4);
//	_brickGenSystem->BrickGenInit();
}

void PlayScene::InitScene()
{
	__InitLetterScene();
	__InitGamePlayScene();

	// System Creations
	_brickGenSystem = new BrickGenSystem(_wall);
	_playerOxySystem = new PlayerOxygenSystem(
		_player, PLAYER_OXYGEN_REDUCE_INITAL_VALUE
	);
	_playerBrickInteractionSystem = new PlayerBricksInteractionSystem(
		_player, _wall, _playerOxySystem
	);

	// RenderSystem Registration
	_renderSystem->RegisterRenderableObject(_gridMapBackground);
	_renderSystem->RegisterRenderableObject(_gridMap);
	_renderSystem->RegisterRenderableObject(_gamePlayUIContainer);


#ifndef NDEBUG
	// A spinning square for performance measure
	_ui = new Container(100, 100, 100, 100);
	_ui->SetDisplay(Display::FLEX);
	_ui->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_ui->SetFlexJustifyContent(FlexJustifyContent::FLEX_START);
	_uiChild1 = new Container(20, 20, 20, 20);
	_uiChild1->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_uiChild2 = new Container(60, 60, 20, 20);
	_ui->AddChildComponent(_uiChild1);
	_ui->AddChildComponent(_uiChild2);
	_uiChild1->EnableBorder(true);
	_uiChild1->SetBorder(0, 255, 0);
	_uiChild2->EnableBorder(true);
	_uiChild2->SetBorder(0, 0, 255);
	_ui->EnableBorder(true);
	_ui->SetBorder(255, 0, 0);
	_ui->SetText(L"Hello!");
	_ui->SetRotationPivot(_ui->GetCenterX(), _ui->GetCenterY());
	TranslateTransition* _transitionTest = 
		new TranslateTransition(
			_ui, 
			_ui->GetX(), _ui->GetY(), 500, 100, 
			3.0, bezier::ease_in_out, 0.0, true
		);
	_ui->AddAnimation(0, _transitionTest);
	_ui->SetState(0);

	_fpsBox = new Container(5, 5, 100, 50);
	_fpsBox->SetFont(24, FontStyleBold);
	_fpsBox->SetText(StringifyFrameRate(0).c_str());

	_testAnimation = new Animation(
		ResourceManager::Get().GetImage(L"motion_sheet"),
		500, 500, true
	);
	_testAnimation->SliceSpriteSheet(32, 32, 0, 0, 32, 32);
	_testAnimation->SetFrameDurations({ 0.2 });
	_testAnimation->Trigger();

	_renderSystem->RegisterRenderableObject(_ui);
	_renderSystem->RegisterRenderableObject(_fpsBox);
	_renderSystem->RegisterRenderableObject(_testAnimation);
#endif

	// Game Play Initialization
	_player->SetPosition(2, 4);
	_brickGenSystem->BrickGenInit();

	// Render the letter scene first
	// _renderSystem->RegisterRenderableObject(_letterComponents.background);
	// _renderSystem->RegisterRenderableObject(_letterContainer);
	
	// Rendering order of the GamePlay scene
	// 1. Background
	// 2. Grid Map
	// 2. GamePlay UI components
	
	

	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::BackGround02, Music::eSoundChannel::BGM);
}

void PlayScene::__InitLetterScene() {
/* Allocate Memory */
	_letterContainer = new Container(0, 0, screenWidth, screenHeight);

	_letterComponents.background = new SingleSpriteRenderable<LetterComponents>();
	
	// LeftBox Elements
	_letterComponents._leftBox = new Container(
		100, 100, screenWidth * 0.50, screenHeight - 100
	);
	_letterComponents.letter = new Container(0, 0, 800, 500);

	_letterComponents.diagrams = new Container(0, 0, 800, 300);
	_letterComponents.leftArrowDiagram = new Container();
	_letterComponents.downArrowDiagram = new Container();
	_letterComponents.rightArrowDiagram = new Container();

	// RightBox Elemenst
	_letterComponents._rightBox = new Container(
		60, 100, screenWidth * 0.50, screenHeight - 100
	);
	_letterComponents.text1 = new Container(0, 0, 800, 50);
	_letterComponents.blessingsOfGod = new Container(0, 0, 800, 600);
	_letterComponents.firstBlessingOfGod = new Container(0, 0, 800, 200);
	_letterComponents.secondBlessingOfGod = new Container(0, 0, 800, 200);
	_letterComponents.thirdBlessingOfGod = new Container(0, 0, 800, 200);
	_letterComponents.text2 = new Container(0, 0, 800, 50);

/* Load Sprites */
	// Letter Scene Sprite Bindings
	_letterComponents.background->BindSprite(
		ResourceManager::Get().GetImage(L"letter_background")
	);
	_letterComponents.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"letter_background")
	);
	_letterComponents.leftArrowDiagram->SetSizeFitImage(true);
	_letterComponents.leftArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"left_arrow_diagram")
	);
	_letterComponents.downArrowDiagram->SetSizeFitImage(true);
	_letterComponents.downArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"down_arrow_diagram")
	);
	_letterComponents.rightArrowDiagram->SetSizeFitImage(true);
	_letterComponents.rightArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"right_arrow_diagram")
	);
	
	// Other Sprite Bindings
	
/* Set UI Component Properties */
	//// Left Box Components
	// TODO: Need a script file seperate.
	// letter scripts
	_letterComponents.letter->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	_letterComponents.letter->SetText(
		L"자랑스러운 라자브 가문의 장녀 라자냐 33세여,\n"
		L"폭탄산 무크티니로 가거라.\n\n"

		L"라자냐의 여전사로서 누구보다 폭탄산 무크티니를 깊게 파\n"
		L"라자브 가문의 전설이 되거라\n\n"

		L"학교를 안 가는걸 명예로 여겨온\n"
		L"라자브 가문의 여자답게 글을 모르겠지.\n"
		L"그림으로 설명하마.");
	_letterComponents.letter->SetFont(24, FontStyleBold);
	// diagrams
	_letterComponents.diagrams->SetPositionLayout(PositionLayout::LAYOUT_STATIC);
	// diagrams flexbox settings
	_letterComponents.diagrams->SetDisplay(Display::FLEX);
	_letterComponents.diagrams->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_letterComponents.diagrams->SetFlexJustifyContent(FlexJustifyContent::SPACE_EVENLY);
	
	//// Right Box Components
	// text1
	_letterComponents.text1->SetFont(24, FontStyleBold);
	_letterComponents.text1->SetText(L"아, 그리고 니 신의 축복이 뭐였지?");
	// blessings of God
	_letterComponents.blessingsOfGod->SetDisplay(Display::BLOCK);
	// first blessing

	// second blessing

	// third blessing

	// text2
	_letterComponents.text2->SetFont(24, FontStyleBold);
	_letterComponents.text2->SetText(L"별 탈 없겠지. 건투를 빈다.");

	// UI Container property
	_letterContainer->SetDisplay(Display::INLINE);

/* Build UI Hierarchy */

	_letterComponents.diagrams->AddChildComponent(
		_letterComponents.leftArrowDiagram
	);
	_letterComponents.diagrams->AddChildComponent(
		_letterComponents.downArrowDiagram
	);
	_letterComponents.diagrams->AddChildComponent(
		_letterComponents.rightArrowDiagram
	);

	// Attach letter to the left box
	_letterComponents._leftBox->AddChildComponent(_letterComponents.letter);
	// Attach diagrams to the left box
	_letterComponents._leftBox->AddChildComponent(_letterComponents.diagrams);

#ifndef NDEBUG	// _leftBox debugging borders
	_letterComponents._leftBox->EnableBorder(true);
	_letterComponents._leftBox->SetBorder(255, 0, 0);
	_letterComponents.letter->EnableBorder(true);
	_letterComponents.letter->SetBorder(255, 0, 0);
	_letterComponents.diagrams->EnableBorder(true);
	_letterComponents.diagrams->SetBorder(255, 0, 0);
	_letterComponents.leftArrowDiagram->EnableBorder(true);
	_letterComponents.leftArrowDiagram->SetBorder(255, 0, 0);
	_letterComponents.downArrowDiagram->EnableBorder(true);
	_letterComponents.downArrowDiagram->SetBorder(255, 0, 0);
	_letterComponents.rightArrowDiagram->EnableBorder(true);
	_letterComponents.rightArrowDiagram->SetBorder(255, 0, 0);
#endif // !NDEBUG

	// Attach blessings
	_letterComponents.blessingsOfGod->AddChildComponent(_letterComponents.firstBlessingOfGod);
	_letterComponents.blessingsOfGod->AddChildComponent(_letterComponents.secondBlessingOfGod);
	_letterComponents.blessingsOfGod->AddChildComponent(_letterComponents.thirdBlessingOfGod);

	// Attach right box contents to the right box
	_letterComponents._rightBox->AddChildComponent(_letterComponents.text1);
	_letterComponents._rightBox->AddChildComponent(_letterComponents.blessingsOfGod);
	_letterComponents._rightBox->AddChildComponent(_letterComponents.text2);

#ifndef NDEBUG	// _rightbox debugging borders
	_letterComponents._rightBox->EnableBorder(true);
	_letterComponents._rightBox->SetBorder(255, 0, 0);
	_letterComponents.text1->EnableBorder(true);
	_letterComponents.text1->SetBorder(255, 0, 0);
	_letterComponents.blessingsOfGod->EnableBorder(true);
	_letterComponents.blessingsOfGod->SetBorder(255, 0, 0);
	_letterComponents.firstBlessingOfGod->EnableBorder(true);
	_letterComponents.firstBlessingOfGod->SetBorder(0, 255, 0);
	_letterComponents.secondBlessingOfGod->EnableBorder(true);
	_letterComponents.secondBlessingOfGod->SetBorder(0, 255, 255);
	_letterComponents.thirdBlessingOfGod->EnableBorder(true);
	_letterComponents.thirdBlessingOfGod->SetBorder(0, 0, 255);
	_letterComponents.text2->EnableBorder(true);
	_letterComponents.text2->SetBorder(255, 0, 0);
#endif // !NDEBUG

	// Attach both left box and right box;
	_letterContainer->AddChildComponent(_letterComponents._leftBox);
	_letterContainer->AddChildComponent(_letterComponents._rightBox);
}

void PlayScene::__InitGamePlayScene() {
	/* Allocate Memory */
	_gamePlayUIContainer = new Container(0, 0, screenWidth, screenHeight);

	// Left Box Components Allocation
	_gamePlayUIComponents._leftBox = new Container(
		0, 0, (screenWidth - 600) * 0.5 + 58, screenHeight
	);
	// TODO: Might need to be animated
	_gamePlayUIComponents.daughter = new Container(0, 0, 385, 465);
	_gamePlayUIComponents.husband = new Container(0, 0, 340, 400);
	_gamePlayUIComponents.mother = new Container(0, 0, 280, 470);;
	_gamePlayUIComponents.dancingTownspeople = new Container(0, 0, 720, 460);
	_gamePlayUIComponents.ancestors = new Container(0, 0, 720, 460);

	// Center Box Components Allocation
	_gamePlayUIComponents._centerBox = new Container(0, 0, 660, screenHeight);
	_gamePlayUIComponents.oxygenMeter = new Container(0, 0, 58, screenHeight);
	_gamePlayUIComponents.meterBackground = new Container(0, 0, 58, screenHeight);
	_gamePlayUIComponents.oxygenLevel = new Container(0, 0, 58, screenHeight - 300);

	// Right Box Components Allocation
	_gamePlayUIComponents._rightBox = new Container(
		0, 0, 540, screenHeight
	);
	_gamePlayUIComponents.scoreBoard = new Container(
		0, 50, 540, 360
	);
	_gamePlayUIComponents.gloryOfFamily = new Container(5, 5, 530, 110);
	_gamePlayUIComponents.honorOfAncestor = new Container(5, 10, 530, 110);
	_gamePlayUIComponents.currentHonor = new Container(5, 15, 530, 110);
	_gamePlayUIComponents.currentState = new Container(0, 300, 540, 580);

	// Grid Map Background
	_gridMapBackground = new SingleSpriteRenderable<GridMap>();

	_gridMap = new GridMap(
		GRID_MAP_POSITION_X, GRID_MAP_POSITION_Y,
		WALL_NUM_ROWS, WALL_NUM_COLS,
		GRID_ITEM_WIDTH, GRID_ITEM_HEIGHT
	);
	_player = new Player();
	_wall = new Wall();

	/* Load Sprites */

	_gridMapBackground->BindSprite(
		ResourceManager::Get().GetImage(L"grid_map_background")
	);
	_gridMapBackground->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"grid_map_background")
	);

	// Player Sprite Bindings
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_02"),
		L"lazanya_02"
	);
	_renderSystem->CachingHelper(_player);


	/* Set UI Component Properties */

#ifndef NDEBUG	// _leftBox debugging borders
	_gamePlayUIComponents._leftBox->EnableFill(true);
	_gamePlayUIComponents._leftBox->SetFillColor(255, 255, 255);
	_gamePlayUIComponents._leftBox->EnableBorder(true);
	_gamePlayUIComponents._leftBox->SetBorder(255, 0, 0);
	_gamePlayUIComponents._centerBox->EnableBorder(true);
	_gamePlayUIComponents._centerBox->SetBorder(0, 255, 0);
	_gamePlayUIComponents._rightBox->EnableFill(true);
	_gamePlayUIComponents._rightBox->SetFillColor(255, 255, 255);
	_gamePlayUIComponents._rightBox->EnableBorder(true);
	_gamePlayUIComponents._rightBox->SetBorder(0, 0, 255);

	_gamePlayUIComponents.daughter->EnableFill(true);
	_gamePlayUIComponents.daughter->SetFillColor(145, 25, 90);
	_gamePlayUIComponents.husband->EnableFill(true);
	_gamePlayUIComponents.husband->SetFillColor(25, 240, 170);
	_gamePlayUIComponents.mother->EnableFill(true);
	_gamePlayUIComponents.mother->SetFillColor(180, 100, 10);
	_gamePlayUIComponents.dancingTownspeople->EnableFill(true);
	_gamePlayUIComponents.dancingTownspeople->SetFillColor(46, 25, 250);
	_gamePlayUIComponents.ancestors->EnableFill(true);
	_gamePlayUIComponents.ancestors->SetFillColor(200, 120, 150);


	_gamePlayUIComponents.scoreBoard->EnableBorder(true);
	_gamePlayUIComponents.scoreBoard->SetBorder(0, 0, 0, 255, 5);
	_gamePlayUIComponents.gloryOfFamily->EnableFill(true);
	_gamePlayUIComponents.gloryOfFamily->SetFillColor(0, 220, 10);
	_gamePlayUIComponents.honorOfAncestor->EnableFill(true);
	_gamePlayUIComponents.honorOfAncestor->SetFillColor(0, 220, 90);
	_gamePlayUIComponents.currentHonor->EnableFill(true);
	_gamePlayUIComponents.currentHonor->SetFillColor(0, 220, 170);
	_gamePlayUIComponents.currentState->EnableFill(true);
	_gamePlayUIComponents.currentState->SetFillColor(0, 220, 250);

	_gridMap->EnableFill(true);
	_gridMap->SetFillColor(125, 125, 255, 125);
#endif // !NDEBUG

	// Left Box Components properties
	// Daughter
	_gamePlayUIComponents.daughter->SetZValue(8);
	_gamePlayUIComponents.daughter->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.daughter->SetPosition(0, screenHeight);
	// Daughter pop-up animation
	IAnimation* daughter_shootup = new TranslateTransition(
		_gamePlayUIComponents.daughter,
		-100, screenHeight, 0, 300, 0.5, bezier::ease_out
	);
	IAnimation* daughter_comedown = new TranslateTransition(
		_gamePlayUIComponents.daughter,
		0, 300, 30, 810, 0.3, bezier::ease_in
	);
	IAnimation* daughter_moveup = new TranslateTransition(
		_gamePlayUIComponents.daughter,
		30, 810, 30, 500, 0.3, bezier::ease_out
	);
	IAnimation* daughter_movedown = new TranslateTransition(
		_gamePlayUIComponents.daughter,
		30, 500, 30, 810, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* daughter_animationPack = new SequentialAnimationPack();
	daughter_animationPack->PushBackAnimation(
		{ daughter_shootup, daughter_comedown, daughter_moveup, daughter_movedown }
	);
	daughter_animationPack->SetLoop(true);
	daughter_animationPack->SetLoopRange(2, 4);
	_gamePlayUIComponents.daughter->AddAnimation(0, daughter_animationPack);
	_gamePlayUIComponents.daughter->SetState(0); // TODO: Debugging purpose;

	// Husband
	_gamePlayUIComponents.husband->SetZValue(10);
	_gamePlayUIComponents.husband->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.husband->SetPosition(0, screenHeight);
	// Husband pop-up animation
	IAnimation* husband_shootup = new TranslateTransition(
		_gamePlayUIComponents.husband,
		-200, screenHeight-100, 160, 100, 0.5, bezier::ease_out
	);
	IAnimation* husband_comedown = new TranslateTransition(
		_gamePlayUIComponents.husband,
		160, 100, 320, 615, 0.3, bezier::ease_in
	);
	IAnimation* husband_moveup = new TranslateTransition(
		_gamePlayUIComponents.husband,
		320, 615, 320, 300, 0.3, bezier::ease_out
	);
	IAnimation* husband_movedown = new TranslateTransition(
		_gamePlayUIComponents.husband,
		320, 300, 320, 615, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* husband_animationPack = new SequentialAnimationPack();
	husband_animationPack->PushBackAnimation(
		{ husband_shootup, husband_comedown, husband_moveup, husband_movedown }
	);
	husband_animationPack->SetLoop(true);
	husband_animationPack->SetLoopRange(2, 4);
	_gamePlayUIComponents.husband->AddAnimation(0, husband_animationPack);
	_gamePlayUIComponents.husband->SetState(0); // TODO: Debugging purpose;

	// Mother
	_gamePlayUIComponents.mother->SetZValue(6);
	_gamePlayUIComponents.mother->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.mother->SetPosition(0, screenHeight);
	// Mother pop-up animation
	IAnimation* mother_shootup = new TranslateTransition(
		_gamePlayUIComponents.mother,
		500, screenHeight-100, 250, 100, 0.5, bezier::ease_out
	);
	IAnimation* mother_comedown = new TranslateTransition(
		_gamePlayUIComponents.mother,
		250, 100, 0, 580, 0.3, bezier::ease_in
	);
	IAnimation* mother_moveup = new TranslateTransition(
		_gamePlayUIComponents.mother,
		0, 580, 0, 280, 0.3, bezier::ease_out
	);
	IAnimation* mother_movedown = new TranslateTransition(
		_gamePlayUIComponents.mother,
		0, 280, 0, 580, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* mother_animationPack = new SequentialAnimationPack();
	mother_animationPack->PushBackAnimation(
		{ mother_shootup, mother_comedown, mother_moveup, mother_movedown }
	);
	mother_animationPack->SetLoop(true);
	mother_animationPack->SetLoopRange(2, 4);
	_gamePlayUIComponents.mother->AddAnimation(0, mother_animationPack);
	_gamePlayUIComponents.mother->SetState(0); // TODO: Debugging purpose;

	// Dancing Townspeople
	_gamePlayUIComponents.dancingTownspeople->SetZValue(4);
	_gamePlayUIComponents.dancingTownspeople->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.dancingTownspeople->SetPosition(0, screenHeight);
	// Dancing Townspeople pop-up animation
	IAnimation* dancingTownspeople_shootup = new TranslateTransition(
		_gamePlayUIComponents.dancingTownspeople,
		0, screenHeight-100, 0, -100, 0.5, bezier::ease_out
	);
	IAnimation* dancingTownspeople_comedown = new TranslateTransition(
		_gamePlayUIComponents.dancingTownspeople,
		0, -100, 0, 345, 0.3, bezier::ease_in
	);
	IAnimation* dancingTownspeople_moveup = new TranslateTransition(
		_gamePlayUIComponents.dancingTownspeople,
		0, 345, 0, 145, 0.3, bezier::ease_out
	);
	IAnimation* dancingTownspeople_movedown = new TranslateTransition(
		_gamePlayUIComponents.dancingTownspeople,
		0, 145, 0, 345, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* dancingTownspeople_animationPack = new SequentialAnimationPack();
	dancingTownspeople_animationPack->PushBackAnimation(
		{ dancingTownspeople_shootup, dancingTownspeople_comedown, dancingTownspeople_moveup, dancingTownspeople_movedown }
	);
	dancingTownspeople_animationPack->SetLoop(true);
	dancingTownspeople_animationPack->SetLoopRange(2, 4);
	_gamePlayUIComponents.dancingTownspeople->AddAnimation(0, dancingTownspeople_animationPack);
	_gamePlayUIComponents.dancingTownspeople->SetState(0); // TODO: Debugging purpose;
	
	// Ancestors
	_gamePlayUIComponents.ancestors->SetZValue(2);
	_gamePlayUIComponents.ancestors->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.ancestors->SetPosition(0, screenHeight);
	// Daughter pop-up animation
	IAnimation* ancestors_shootup = new TranslateTransition(
		_gamePlayUIComponents.ancestors,
		0, screenHeight, 0, 0, 1.5, bezier::ease_in_out
	);
	IAnimation* ancestors_comedown = new TranslateTransition(
		_gamePlayUIComponents.ancestors,
		0, 0, 0, 30, 1, bezier::ease_in
	);
	IAnimation* ancestors_moveup = new TranslateTransition(
		_gamePlayUIComponents.ancestors,
		0, 30, 0, -10, 0.5, bezier::ease_out
	);
	IAnimation* ancestors_movedown = new TranslateTransition(
		_gamePlayUIComponents.ancestors,
		0, -10, 0, 30, 0.5, bezier::ease_in
	);
	SequentialAnimationPack* ancestors_animationPack = new SequentialAnimationPack();
	ancestors_animationPack->PushBackAnimation(
		{ ancestors_shootup, ancestors_comedown, ancestors_moveup, ancestors_movedown }
	);
	ancestors_animationPack->SetLoop(true);
	ancestors_animationPack->SetLoopRange(2, 4);
	_gamePlayUIComponents.ancestors->AddAnimation(0, ancestors_animationPack);
	_gamePlayUIComponents.ancestors->SetState(0); // TODO: Debugging purpose;
	

	// Center Box Components properties
	_gamePlayUIComponents._centerBox->SetDisplay(Display::BLOCK);
	_gamePlayUIComponents.oxygenMeter->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.oxygenMeter->SetPosition(600, 0);
	_gamePlayUIComponents.oxygenMeter->EnableBorder(true);
	_gamePlayUIComponents.oxygenMeter->SetBorder(0, 0, 0, -1, 5.f);
	_gamePlayUIComponents.oxygenMeter->SetZValue(10);
	_gamePlayUIComponents.meterBackground->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.meterBackground->SetPosition(600, 0);
	_gamePlayUIComponents.meterBackground->EnableFill(true);
	_gamePlayUIComponents.meterBackground->SetFillColor(255, 255, 255);
	_gamePlayUIComponents.oxygenLevel->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_gamePlayUIComponents.oxygenLevel->SetPosition(600, 0);
	_gamePlayUIComponents.oxygenLevel->SetZValue(5);
	_gamePlayUIComponents.oxygenLevel->SetY(300);
	_gamePlayUIComponents.oxygenLevel->EnableFill(true);
	_gamePlayUIComponents.oxygenLevel->SetFillColor(0, 120, 240);

	// Right Box Components properties
	_gamePlayUIComponents._rightBox->SetDisplay(Display::BLOCK);
	_gamePlayUIComponents.scoreBoard->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_gamePlayUIComponents.gloryOfFamily->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_gamePlayUIComponents.gloryOfFamily->SetText(__WStringifyGloryHall(10).c_str());
	_gamePlayUIComponents.gloryOfFamily->SetFont(52, FontStyleBold);
	_gamePlayUIComponents.gloryOfFamily->SetTextPosition(5, 25);
	_gamePlayUIComponents.honorOfAncestor->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_gamePlayUIComponents.honorOfAncestor->SetText(__WStringifyMothersHonor(10).c_str());
	_gamePlayUIComponents.honorOfAncestor->SetFont(52, FontStyleBold);
	_gamePlayUIComponents.honorOfAncestor->SetTextPosition(5, 25);
	_gamePlayUIComponents.currentHonor->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_gamePlayUIComponents.currentHonor->SetText(__WStringifyCurrentHonor(10).c_str());
	_gamePlayUIComponents.currentHonor->SetFont(52, FontStyleBold);
	_gamePlayUIComponents.currentHonor->SetTextPosition(5, 25);
	_gamePlayUIComponents.currentState->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);


	// The UI Container
	_gamePlayUIContainer->SetDisplay(Display::FLEX);
	_gamePlayUIContainer->SetFlexJustifyContent(FlexJustifyContent::FLEX_START);


	_gridMapBackground->SetPosition(screenWidth >> 1, screenHeight >> 1);
	_gridMapBackground->UpdateSpritePivotPosition(H_DIRECTION::CENTER, V_DIRECTION::CENTER);

	_player->ChangeTag(L"lazanya_02");

/* Build UI Hierarchy */
	// Left Box Components
	_gamePlayUIComponents._leftBox->AddChildComponent(_gamePlayUIComponents.daughter);
	_gamePlayUIComponents._leftBox->AddChildComponent(_gamePlayUIComponents.husband);
	_gamePlayUIComponents._leftBox->AddChildComponent(_gamePlayUIComponents.mother);
	_gamePlayUIComponents._leftBox->AddChildComponent(_gamePlayUIComponents.dancingTownspeople);
	_gamePlayUIComponents._leftBox->AddChildComponent(_gamePlayUIComponents.ancestors);

	// Center Box Components
	_gamePlayUIComponents._centerBox->AddChildComponent(_gamePlayUIComponents.oxygenMeter);
	_gamePlayUIComponents._centerBox->AddChildComponent(_gamePlayUIComponents.meterBackground);
	_gamePlayUIComponents._centerBox->AddChildComponent(_gamePlayUIComponents.oxygenLevel);

	// Right Box Components
	_gamePlayUIComponents.scoreBoard->AddChildComponent(_gamePlayUIComponents.gloryOfFamily);
	_gamePlayUIComponents.scoreBoard->AddChildComponent(_gamePlayUIComponents.honorOfAncestor);
	_gamePlayUIComponents.scoreBoard->AddChildComponent(_gamePlayUIComponents.currentHonor);
	_gamePlayUIComponents._rightBox->AddChildComponent(_gamePlayUIComponents.scoreBoard);
	_gamePlayUIComponents._rightBox->AddChildComponent(_gamePlayUIComponents.currentState);

	// Bind Player and Wall to GridMap
	_gridMap->AddGridItem(_wall);
	_gridMap->AddGridItem(_player);

	// UI Container binding
	_gamePlayUIContainer->AddChildComponent(_gamePlayUIComponents._leftBox);
	_gamePlayUIContainer->AddChildComponent(_gamePlayUIComponents._centerBox);
	_gamePlayUIContainer->AddChildComponent(_gamePlayUIComponents._rightBox);

}

void PlayScene::Update(const double deltaTime)
{
	if (!DidInit)
	{
		InitScene();
		DidInit = true;
	}


#ifndef NDEBUG
	_elapsedTime += deltaTime;
	_frames += 1;
	if (_elapsedTime >= 1.0) {
		_fpsBox->SetText(StringifyFrameRate(_frames).c_str());
		_elapsedTime -= 1.0;
		_frames = 0;
	}
	_testAnimation->Update(deltaTime);
#endif

	//_ui->Rotate(deltaTime*100);
	_ui->Update(deltaTime);
	PlayerUpdate(deltaTime);
	_gamePlayUIComponents.daughter->Update(deltaTime);
	_gamePlayUIComponents.husband->Update(deltaTime);
	_gamePlayUIComponents.mother->Update(deltaTime);
	_gamePlayUIComponents.dancingTownspeople->Update(deltaTime);
	_gamePlayUIComponents.ancestors->Update(deltaTime);
	

#ifdef PLAYSCENE
	if (/*!°¡Á··ÂÀ» ¼±ÅÃÇß´Â°¡?*/)
	{
		//TODO: °¡Á··Â ¼±ÅÃ ÀÌÀüÀÇ ¾÷µ¥ÀÌÆ®.

		_renderSystem->ClearRenderableRegistry();

		//°ÔÀÓ ½ÃÀÛ½Ã ÇÊ¿äÇÑrendererµî·Ï
		_renderSystem->RegisterRenderableObject(dynamic_cast<IRenderable*>(player));
	}
	else//°¡Á··ÂÀ» °ñ¶ú´Ù¸é
	{
		/*player=new Decorators*/
		//TODO: ½ÇÁ¦ °ÔÀÓ ¾÷µ¥ÀÌÆ®
	}
#endif
}

void PlayScene::Draw()
{
	_renderSystem->Render();
#ifdef PLAYSCENE
	if (/*!°¡Á··ÂÀ» ¼±ÅÃÇß´Â°¡?*/)
	{

		_renderSystem->Render();
		//TODO: °¡Á··Â ¼±ÅÃ ÀÌÀüÀÇ ¾÷µ¥ÀÌÆ®.
	}
	else//°¡Á··ÂÀ» °ñ¶ú´Ù¸é
	{
		_renderSystem->Render();
		//TODO: ½ÇÁ¦ °ÔÀÓ ·»´õ
	}
#endif
}



void PlayScene::EndScene()
{

}

void PlayScene::PlayerUpdate(const double deltaTime)
{
	_player->Update(deltaTime);
	//comboDuration++
	_player->AddComboElapsedTime(deltaTime);

	//Set to combo 0 every ComboDuration second
	if (_player->GetComboElapsedTime() >= _player->GetComboDuration())
	{
		_player->SetCombo(0);
		_player->AddComboElapsedTime(-1);
	}
	//if getkey Down, MoveDown.
	if (Input::inputManager->IsTurnDn(VK_DOWN))
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY() + 1, _player->GetPositionX(),
			VK_DOWN, _countWallPop,deltaTime);
	}
	//if getkey Left and it's in the play screen and if brick type is not NONE, MoveLeft
	if (Input::inputManager->IsTurnDn(VK_LEFT)
		&& _player->GetPositionX() > 0
		&& _wall->GetBrick(_player->GetPositionY(), _player->GetPositionX() - 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() - 1,
			VK_LEFT, _countWallPop,deltaTime);
	}
	//if getkey Right and it's in the play screen and if brick type is not NONE, MoveRight
	if (Input::inputManager->IsTurnDn(VK_RIGHT)
		&& _player->GetPositionX() < 4
		&& _wall->GetBrick(_player->GetPositionY(), _player->GetPositionX() + 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() + 1,
			VK_RIGHT, _countWallPop,deltaTime);
	}
	//if pop wall three time
	if (_countWallPop == 3)
	{
		_brickGenSystem->GenerateNextRows();
		_countWallPop = 0;
	}
	//player oxygen system
	_playerOxySystem->ReduceOxygen(deltaTime);

	//Doing Debug:
	//Debug.Log(_playerOxySystem->GetAmountOfReduceOxy());
}
