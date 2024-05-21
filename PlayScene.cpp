#include "PlayScene.h"

// Game Components
#include "GridMap.h"
#include "Player.h"
#include "Wall.h"

// Graphics
#include "SingleRenderable.h"
#include "Container.h"
#include "PlayerStateContainer.h"
#include "Animation.h"
#include "SequentialAnimationPack.h"

// Decorators
#include "TenaciousDwarf.h"
#include "Wimp.h"
#include "Pummeler.h"
#include "SugarGirl.h"
#include "Anaerobic.h"
#include "Naughty.h"
#include "GoldSeeker.h"

// System
#include "BrickGenerationSystem.h"
#include "PlayerBricksInteractionSystem.h"
#include "PlayerOxygenSystem.h"

// Resource
#include "ResourceManager.h"

constexpr double PLAYER_OXYGEN_REDUCE_INITAL_VALUE = 10.0;

using namespace Gdiplus;

PlayScene::PlayScene() {	
	__InitComponents();
	__InitSystems();
	_initialized = true;
}

PlayScene::~PlayScene() {

}

void PlayScene::__InitComponents() {

/********** Allocate Memory **********/

	_gamePlayUIContainer = new Container(0, 0, screenWidth, screenHeight);

	// Left Box Components Allocation
	_uiComps._leftBox = new Container(
		0, 0, (screenWidth - 600) * 0.5 + 58, screenHeight
	);
	// TODO: Might need to be animated
	_uiComps.daughter = new Container(0, 0, 385, 465);
	_uiComps.husband = new Container(0, 0, 340, 400);
	_uiComps.mother = new Container(0, 0, 280, 470);;
	_uiComps.dancingTownspeople = new Container(0, 0, 720, 460);
	_uiComps.ancestors = new Container(0, 0, 720, 460);

	// Center Box Components Allocation
	_uiComps._centerBox = new Container(0, 0, 660, screenHeight);
	_uiComps.levelUpSign = new Container(0, 0, 600, 200);
	_uiComps.startMessage = new Container(0, 0, 100, 36);
	_uiComps.adBox = new Container(0, 0, 200, 150);
	_uiComps.adText = new Container(0, 0, 144, 48);
	_uiComps.adValue = new Container(0, 0, 128, 64);
	_uiComps.comboBox = new Container(0, 0, 200, 150);
	_uiComps.comboText = new Container(0, 0, 144, 48);
	_uiComps.comboValue = new Container(0, 0, 128, 64);

	_uiComps.oxygenMeter = new Container(0, 0, 58, screenHeight);
	_uiComps.meterBackground = new Container(0, 0, 58, screenHeight);
	_uiComps.oxygenLevel = new Container(0, 0, 58, screenHeight);

	// Right Box Components Allocation
	_uiComps._rightBox = new Container(
		0, 0, 540, screenHeight
	);
	_uiComps.scoreBoard = new Container(
		0, 50, 540, 360
	);
	_uiComps.gloryOfFamily = new Container(5, 5, 530, 110);
	_uiComps.honorOfAncestor = new Container(5, 10, 530, 110);
	_uiComps.currentHonor = new Container(5, 15, 530, 110);
	_uiComps.currentState = new PlayerStateContainer(0, 300, 540, 580);

	// Grid Map Background
	_gridMapBackground = new SingleSpriteRenderable<GridMap>();

	_gridMap = new GridMap(
		GRID_MAP_POSITION_X, GRID_MAP_POSITION_Y,
		WALL_NUM_ROWS, WALL_NUM_COLS,
		GRID_ITEM_WIDTH, GRID_ITEM_HEIGHT
	);
	_player = new Player();
	_wall = new Wall();

/********** Load Sprites **********/

	_gridMapBackground->BindSprite(
		ResourceManager::Get().GetImage(L"grid_map_background")
	);
	_gridMapBackground->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"grid_map_background")
	);

	// Player Sprite Bindings
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_1_0_1"),
		L"right_idle"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_1_0_2"),
		L"left_idle"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_2_0_1"),
		L"right_attack"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_2_0_2"),
		L"left_attack"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_3_0_1"),
		L"left_move"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_3_0_2"),
		L"right_move"
	);
	_renderSystem->CachingHelper(_player);


/********** Set UI Component Properties **********/

#ifndef NDEBUG	// Performance measure
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
#endif

#ifndef NDEBUG	// _leftBox debugging borders
	_uiComps._leftBox->EnableFill(true);
	_uiComps._leftBox->SetFillColor(255, 255, 255);
	_uiComps._leftBox->EnableBorder(true);
	_uiComps._leftBox->SetBorder(255, 0, 0);
	_uiComps._centerBox->EnableBorder(true);
	_uiComps._centerBox->SetBorder(0, 255, 0);
	_uiComps._rightBox->EnableFill(true);
	_uiComps._rightBox->SetFillColor(255, 255, 255);
	_uiComps._rightBox->EnableBorder(true);
	_uiComps._rightBox->SetBorder(0, 0, 255);

	_uiComps.daughter->EnableFill(true);
	_uiComps.daughter->SetFillColor(145, 25, 90);
	_uiComps.husband->EnableFill(true);
	_uiComps.husband->SetFillColor(25, 240, 170);
	_uiComps.mother->EnableFill(true);
	_uiComps.mother->SetFillColor(180, 100, 10);
	_uiComps.dancingTownspeople->EnableFill(true);
	_uiComps.dancingTownspeople->SetFillColor(46, 25, 250);
	_uiComps.ancestors->EnableFill(true);
	_uiComps.ancestors->SetFillColor(200, 120, 150);

	_uiComps.levelUpSign->EnableBorder(true);
	_uiComps.levelUpSign->SetBorder(250, 0, 0);
	_uiComps.startMessage->EnableBorder(true);
	_uiComps.startMessage->SetBorder(150, 250, 0);
	_uiComps.adBox->EnableFill(true);
	_uiComps.adBox->SetFillColor(100, 250, 100);
	_uiComps.adText->EnableBorder(true);
	_uiComps.adText->SetBorder(90, 126, 230);
	_uiComps.adValue->EnableBorder(true);
	_uiComps.adValue->SetBorder(210, 46, 120);
	_uiComps.comboBox->EnableFill(true);
	_uiComps.comboBox->SetFillColor(100, 250, 100);

	_uiComps.scoreBoard->EnableBorder(true);
	_uiComps.scoreBoard->SetBorder(0, 0, 0, 255, 5);
	_uiComps.gloryOfFamily->EnableFill(true);
	_uiComps.gloryOfFamily->SetFillColor(0, 220, 10);
	_uiComps.honorOfAncestor->EnableFill(true);
	_uiComps.honorOfAncestor->SetFillColor(0, 220, 90);
	_uiComps.currentHonor->EnableFill(true);
	_uiComps.currentHonor->SetFillColor(0, 220, 170);
	_uiComps.currentState->EnableFill(true);
	_uiComps.currentState->SetFillColor(0, 220, 250, 20);

#endif // !NDEBUG


	// Left Box Components properties
	// Daughter
	_uiComps.daughter->SetZValue(8);
	_uiComps.daughter->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.daughter->SetPosition(0, screenHeight);
	// Daughter pop-up animation
	IAnimation* daughter_shootup = new TranslateTransition(
		_uiComps.daughter,
		-100, screenHeight, 0, 300, 0.5, bezier::ease_out
	);
	IAnimation* daughter_comedown = new TranslateTransition(
		_uiComps.daughter,
		0, 300, 30, 810, 0.3, bezier::ease_in
	);
	IAnimation* daughter_moveup = new TranslateTransition(
		_uiComps.daughter,
		30, 810, 30, 600, 0.3, bezier::ease_out
	);
	IAnimation* daughter_movedown = new TranslateTransition(
		_uiComps.daughter,
		30, 600, 30, 810, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* daughter_animationPack = new SequentialAnimationPack();
	daughter_animationPack->PushBackAnimation(
		{ daughter_shootup, daughter_comedown, daughter_moveup, daughter_movedown }
	);
	daughter_animationPack->SetLoop(true);
	daughter_animationPack->SetLoopRange(2, 4);
	_uiComps.daughter->AddAnimation(0, daughter_animationPack);

	// Husband
	_uiComps.husband->SetZValue(10);
	_uiComps.husband->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.husband->SetPosition(0, screenHeight);
	// Husband pop-up animation
	IAnimation* husband_shootup = new TranslateTransition(
		_uiComps.husband,
		-200, screenHeight-100, 160, 100, 0.5, bezier::ease_out
	);
	IAnimation* husband_comedown = new TranslateTransition(
		_uiComps.husband,
		160, 100, 320, 615, 0.3, bezier::ease_in
	);
	IAnimation* husband_moveup = new TranslateTransition(
		_uiComps.husband,
		320, 615, 320, 400, 0.3, bezier::ease_out
	);
	IAnimation* husband_movedown = new TranslateTransition(
		_uiComps.husband,
		320, 400, 320, 615, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* husband_animationPack = new SequentialAnimationPack();
	husband_animationPack->PushBackAnimation(
		{ husband_shootup, husband_comedown, husband_moveup, husband_movedown }
	);
	husband_animationPack->SetLoop(true);
	husband_animationPack->SetLoopRange(2, 4);
	_uiComps.husband->AddAnimation(0, husband_animationPack);

	// Mother
	_uiComps.mother->SetZValue(6);
	_uiComps.mother->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.mother->SetPosition(0, screenHeight);
	// Mother pop-up animation
	IAnimation* mother_shootup = new TranslateTransition(
		_uiComps.mother,
		500, screenHeight-100, 250, 100, 0.5, bezier::ease_out
	);
	IAnimation* mother_comedown = new TranslateTransition(
		_uiComps.mother,
		250, 100, 0, 580, 0.3, bezier::ease_in
	);
	IAnimation* mother_moveup = new TranslateTransition(
		_uiComps.mother,
		0, 580, 0, 380, 0.3, bezier::ease_out
	);
	IAnimation* mother_movedown = new TranslateTransition(
		_uiComps.mother,
		0, 380, 0, 580, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* mother_animationPack = new SequentialAnimationPack();
	mother_animationPack->PushBackAnimation(
		{ mother_shootup, mother_comedown, mother_moveup, mother_movedown }
	);
	mother_animationPack->SetLoop(true);
	mother_animationPack->SetLoopRange(2, 4);
	_uiComps.mother->AddAnimation(0, mother_animationPack);

	// Dancing Townspeople
	_uiComps.dancingTownspeople->SetZValue(4);
	_uiComps.dancingTownspeople->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.dancingTownspeople->SetPosition(0, screenHeight);
	// Dancing Townspeople pop-up animation
	IAnimation* dancingTownspeople_shootup = new TranslateTransition(
		_uiComps.dancingTownspeople,
		0, screenHeight-100, 0, -100, 0.5, bezier::ease_out
	);
	IAnimation* dancingTownspeople_comedown = new TranslateTransition(
		_uiComps.dancingTownspeople,
		0, -100, 0, 345, 0.3, bezier::ease_in
	);
	IAnimation* dancingTownspeople_moveup = new TranslateTransition(
		_uiComps.dancingTownspeople,
		0, 345, 0, 195, 0.3, bezier::ease_out
	);
	IAnimation* dancingTownspeople_movedown = new TranslateTransition(
		_uiComps.dancingTownspeople,
		0, 195, 0, 345, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* dancingTownspeople_animationPack = new SequentialAnimationPack();
	dancingTownspeople_animationPack->PushBackAnimation(
		{ dancingTownspeople_shootup, dancingTownspeople_comedown, dancingTownspeople_moveup, dancingTownspeople_movedown }
	);
	dancingTownspeople_animationPack->SetLoop(true);
	dancingTownspeople_animationPack->SetLoopRange(2, 4);
	_uiComps.dancingTownspeople->AddAnimation(0, dancingTownspeople_animationPack);
	
	// Ancestors
	_uiComps.ancestors->SetZValue(2);
	_uiComps.ancestors->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.ancestors->SetPosition(0, screenHeight);
	// Daughter pop-up animation
	IAnimation* ancestors_shootup = new TranslateTransition(
		_uiComps.ancestors,
		0, screenHeight, 0, 0, 1.5, bezier::ease_in_out
	);
	IAnimation* ancestors_comedown = new TranslateTransition(
		_uiComps.ancestors,
		0, 0, 0, 30, 1, bezier::ease_in
	);
	IAnimation* ancestors_moveup = new TranslateTransition(
		_uiComps.ancestors,
		0, 30, 0, -10, 0.5, bezier::ease_out
	);
	IAnimation* ancestors_movedown = new TranslateTransition(
		_uiComps.ancestors,
		0, -10, 0, 30, 0.5, bezier::ease_in
	);
	SequentialAnimationPack* ancestors_animationPack = new SequentialAnimationPack();
	ancestors_animationPack->PushBackAnimation(
		{ ancestors_shootup, ancestors_comedown, ancestors_moveup, ancestors_movedown }
	);
	ancestors_animationPack->SetLoop(true);
	ancestors_animationPack->SetLoopRange(2, 4);
	_uiComps.ancestors->AddAnimation(0, ancestors_animationPack);
	
	// Center Box Components properties
	_uiComps._centerBox->SetDisplay(Display::BLOCK);
	
	// LevelUp Sign
	_uiComps.levelUpSign->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.levelUpSign->SetPosition(0, 200);
	
	// Start Message
	_uiComps.startMessage->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.startMessage->SetPosition(260, 340);
	_uiComps.startMessage->SetFontFamily(L"Broadway");
	_uiComps.startMessage->SetFontColor(220, 220, 220, 120);
	_uiComps.startMessage->SetFont(24, FontStyleBold);
	_uiComps.startMessage->SetText(L"Press ↓");

	// attackDamageBox?
	_uiComps.adBox->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.adBox->SetPosition(0, 50);
	_uiComps.adBox->SetDisplay(Display::FLEX);
	_uiComps.adBox->SetFlexDirection(FlexDirection::COLUMN);
	_uiComps.adBox->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_uiComps.adBox->SetFlexJustifyContent(FlexJustifyContent::SPACE_AROUND);
	_uiComps.adText->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.adText->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_uiComps.adText->SetFont(32, FontStyleBold);
	_uiComps.adText->SetText(L"공격력");
	_uiComps.adValue->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.adValue->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_uiComps.adValue->SetFont(62, FontStyleBold);
	_uiComps.adValue->SetText(L"00");
	

	// comboBox
	_uiComps.comboBox->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.comboBox->SetPosition(400, 50);
	_uiComps.comboBox->SetDisplay(Display::FLEX);
	_uiComps.comboBox->SetFlexDirection(FlexDirection::COLUMN);
	_uiComps.comboBox->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_uiComps.comboBox->SetFlexJustifyContent(FlexJustifyContent::SPACE_AROUND);
	_uiComps.comboText->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.comboText->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_uiComps.comboText->SetFont(32, FontStyleBold);
	_uiComps.comboText->SetText(L"콤보");
	_uiComps.comboValue->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.comboValue->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_uiComps.comboValue->SetFont(62, FontStyleBold);
	_uiComps.comboValue->SetText(L"00");

	// Oxygen Level
	_uiComps.oxygenMeter->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.oxygenMeter->SetPosition(600, 0);
	_uiComps.oxygenMeter->EnableBorder(true);
	_uiComps.oxygenMeter->SetBorder(0, 0, 0, -1, 5.f);
	_uiComps.oxygenMeter->SetZValue(10);
	_uiComps.meterBackground->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.meterBackground->SetPosition(600, 0);
	_uiComps.meterBackground->EnableFill(true);
	_uiComps.meterBackground->SetFillColor(255, 255, 255);
	_uiComps.oxygenLevel->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.oxygenLevel->SetPosition(600, 0);
	_uiComps.oxygenLevel->SetZValue(5);
	_uiComps.oxygenLevel->EnableFill(true);
	_uiComps.oxygenLevel->SetFillColor(0, 120, 240);

	// Right Box Components properties
	_uiComps._rightBox->SetDisplay(Display::BLOCK);
	_uiComps.scoreBoard->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.gloryOfFamily->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.gloryOfFamily->SetFont(52, FontStyleBold);
	_uiComps.gloryOfFamily->SetTextPosition(5, 25);
	_uiComps.honorOfAncestor->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.honorOfAncestor->SetFont(52, FontStyleBold);
	_uiComps.honorOfAncestor->SetTextPosition(5, 25);
	_uiComps.currentHonor->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.currentHonor->SetFont(52, FontStyleBold);
	_uiComps.currentHonor->SetTextPosition(5, 25);
	
	
	// Add Animations in the currentState.
	_uiComps.currentState->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);


	// The UI Container
	_gamePlayUIContainer->SetDisplay(Display::FLEX);
	_gamePlayUIContainer->SetFlexJustifyContent(FlexJustifyContent::FLEX_START);


	_gridMapBackground->SetPosition(screenWidth >> 1, screenHeight >> 1);
	_gridMapBackground->UpdateSpritePivotPosition(H_DIRECTION::CENTER, V_DIRECTION::CENTER);

	

/********** Build UI Hierarchy **********/

	// Left Box Components
	_uiComps._leftBox->AddChildComponent(_uiComps.daughter);
	_uiComps._leftBox->AddChildComponent(_uiComps.husband);
	_uiComps._leftBox->AddChildComponent(_uiComps.mother);
	_uiComps._leftBox->AddChildComponent(_uiComps.dancingTownspeople);
	_uiComps._leftBox->AddChildComponent(_uiComps.ancestors);

	// Center Box Components
	_uiComps.adBox->AddChildComponent(_uiComps.adText);
	_uiComps.adBox->AddChildComponent(_uiComps.adValue);

	_uiComps.comboBox->AddChildComponent(_uiComps.comboText);
	_uiComps.comboBox->AddChildComponent(_uiComps.comboValue);

	_uiComps._centerBox->AddChildComponent(_uiComps.oxygenMeter);
	_uiComps._centerBox->AddChildComponent(_uiComps.meterBackground);
	_uiComps._centerBox->AddChildComponent(_uiComps.oxygenLevel);
	_uiComps._centerBox->AddChildComponent(_uiComps.levelUpSign);
	_uiComps._centerBox->AddChildComponent(_uiComps.startMessage);
	_uiComps._centerBox->AddChildComponent(_uiComps.adBox);
	_uiComps._centerBox->AddChildComponent(_uiComps.comboBox);

	// Right Box Components
	_uiComps.scoreBoard->AddChildComponent(_uiComps.gloryOfFamily);
	_uiComps.scoreBoard->AddChildComponent(_uiComps.honorOfAncestor);
	_uiComps.scoreBoard->AddChildComponent(_uiComps.currentHonor);


	_uiComps._rightBox->AddChildComponent(_uiComps.scoreBoard);
	_uiComps._rightBox->AddChildComponent(_uiComps.currentState);

	// Bind Player and Wall to GridMap
	_gridMap->AddGridItem(_wall);
	_gridMap->AddGridItem(_player);

	// UI Container binding
	_gamePlayUIContainer->AddChildComponent(_uiComps._leftBox);
	_gamePlayUIContainer->AddChildComponent(_uiComps._centerBox);
	_gamePlayUIContainer->AddChildComponent(_uiComps._rightBox);

}

void PlayScene::__InitSystems() {
	_brickGenSystem = new BrickGenSystem(_wall,_player);
	_playerOxySystem = new PlayerOxygenSystem(
		_player, PLAYER_OXYGEN_REDUCE_INITAL_VALUE
	);
	_playerBrickInteractionSystem = new PlayerBricksInteractionSystem(
		_player, _wall, _playerOxySystem
	);
}

void PlayScene::Update(const double deltaTime)
{
	if (!_player->IsDead() && 
		Input::inputManager->IsTurnDn(VK_DOWN)) {
		_started = true;
		_uiComps.startMessage->SetText(L"");
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

	if (_started) {
#ifndef NDEBUG
		//_ui->Rotate(deltaTime*100);
		_ui->Update(deltaTime);
#endif
		
		// Update player
		__PlayerUpdate(deltaTime);

		// Trigger NPC animation if any condition meets;
		__TriggerNPCsAnimations();

		// Update NPCs
		_uiComps.daughter->Update(deltaTime);
		_uiComps.husband->Update(deltaTime);
		_uiComps.mother->Update(deltaTime);
		_uiComps.dancingTownspeople->Update(deltaTime);
		_uiComps.ancestors->Update(deltaTime);

		// Update Scores
		_uiComps.currentHonor->SetText(__WStringifyCurrentHonor(_player->GetCurrScore()).c_str());
	
		// Update Oxygen Level.
		double oxygenRate = _player->GetCurrOxyLevel() / _player->GetMaxOxyLevel();
		_uiComps.oxygenLevel->SetY(screenHeight * (1.0 - oxygenRate));

		// Update Attack Damage
		_uiComps.adValue->SetText(
			__WStringifyAD(_player->GetAttackDamage()).c_str()
		);

		// Update Combo
		_uiComps.comboValue->SetText(
			__WStringifyCombos(_player->GetCurrCombo()).c_str()
		);

		// Update Player State
		_stateUpdateElapsedTime += deltaTime;
		_uiComps.currentState->Update(deltaTime);
		if (_stateUpdateElapsedTime >= _stateUpdateDuration) {
			_stateUpdateElapsedTime -= _stateUpdateDuration;
			
			if (_buttonPressedCount <= 3) {
				_uiComps.currentState->SetState(
					static_cast<int>(PlayerStateAnimation::IDLE)
				);
			}
			else if (_buttonPressedCount <= 6) {
				_uiComps.currentState->SetState(
					static_cast<int>(PlayerStateAnimation::WARMING)
				);
			}
			else {
				_uiComps.currentState->SetState(
					static_cast<int>(PlayerStateAnimation::BURNING)
				);
			}

			_buttonPressedCount = 0;
		}
	}
	

	// Check if the player is dead
	if (_player->IsDead()) {
		// Stop the update
		_started = false;
		_ended = true;
		// Set State image
		_uiComps.currentState->SetState(
			static_cast<int>(PlayerStateAnimation::DEAD)
		);

		// Show pop up windows
		// Game end
		// Or retry -> need thorough init process!
	}
}

void PlayScene::Draw()
{
	_renderSystem->Render();
}

void PlayScene::InitScene()
{
	__ResetGame();

	// RenderSystem Registration
	_renderSystem->RegisterRenderableObject(_gridMapBackground);
	_renderSystem->RegisterRenderableObject(_gridMap);
	_renderSystem->RegisterRenderableObject(_gamePlayUIContainer);

#ifndef NDEBUG	// Performance measure
	_renderSystem->RegisterRenderableObject(_ui);
	_renderSystem->RegisterRenderableObject(_fpsBox);
	_renderSystem->RegisterRenderableObject(_testAnimation);
#endif

	// Rendering order of the GamePlay scene
	// 1. Background
	// 2. Grid Map
	// 2. GamePlay UI components
	
	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::BackGround02, Music::eSoundChannel::BGM);
}

void PlayScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}

void PlayScene::__PlayerUpdate(const double deltaTime)
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

	// DOWN arrow key pressed
	if (Input::inputManager->IsTurnDn(VK_DOWN))
	{
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Effect);


		_player->TriggerEffect(PlayerEffect::DOWN_ATTACK);
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY() + 1, _player->GetPositionX(),
			VK_DOWN, _countWallPop, deltaTime
		);

		if (_player->IsFacingLeft())
			_player->ChangeTag(L"left_attack");
		else
			_player->ChangeTag(L"right_attack");

		++_buttonPressedCount;
	}

	// DOWN arrow key up
	if (Input::inputManager->IsTurnUp(VK_DOWN)) {
		if (_player->IsFacingLeft())
			_player->ChangeTag(L"left_idle");
		else
			_player->ChangeTag(L"right_idle");
	}

	// LEFT arrow key is pressed
	if (Input::inputManager->IsTurnDn(VK_LEFT) && 
		_player->GetPositionX() > 0 && 
		_wall->GetBrick(_player->GetPositionY(), _player->GetPositionX() - 1).type
		!= BrickType::NONE) {
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Effect);

		// Play the left attack effect
		_player->TriggerEffect(PlayerEffect::LEFT_ATTACK);

		// Change the player pose
		_player->ChangeTag(L"left_attack");
		_player->SetFacingRight(true);

		// Damage Brick
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY(), 
			_player->GetPositionX() - 1,
			VK_LEFT, _countWallPop, deltaTime
		);

		++_buttonPressedCount;
	}

	// LEFT arrow key is up
	if (Input::inputManager->IsTurnUp(VK_LEFT)) {
		_player->ChangeTag(L"left_move");
	}
	
	// RIGHT arrow key is pressed
	if (Input::inputManager->IsTurnDn(VK_RIGHT) &&
		_player->GetPositionX() < 4 &&
		_wall->GetBrick(
			_player->GetPositionY(),
			_player->GetPositionX() + 1
		).type != BrickType::NONE) {
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Effect);

		// Play the right attack effect
		_player->TriggerEffect(PlayerEffect::RIGHT_ATTACK);

		// Change the player pose
		_player->ChangeTag(L"right_attack");
		_player->SetFacingRight(true);

		// Damage Brick
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY(),
			_player->GetPositionX() + 1,
			VK_RIGHT, _countWallPop, deltaTime
		);

		++_buttonPressedCount;
	}

	// RIGHT arrow key is up
	if (Input::inputManager->IsTurnUp(VK_RIGHT)) {
		_player->ChangeTag(L"right_move");
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

void PlayScene::__TriggerNPCsAnimations() {
	if (!_npcEmerged[0] && 
		_player->GetCurrScore() >= 0) {
		_uiComps.husband->SetState(0);
		_npcEmerged[0] = true;
	}
	if (!_npcEmerged[1] && 
		_player->GetCurrScore() >= 30) {
		_uiComps.daughter->SetState(0);
		_npcEmerged[1] = true;
	}
	if (!_npcEmerged[2] && 
		_player->GetCurrScore() >= 60) {
		_uiComps.dancingTownspeople->SetState(0);
		_npcEmerged[2] = true;
	}
	if (!_npcEmerged[3] && 
		_player->GetCurrScore() >= _mothersScore) {
		_uiComps.mother->SetState(0);
		_npcEmerged[3] = true;
	}
	if (!_npcEmerged[4] && 
		_player->GetCurrScore() >= _gloryOfFamilyScore) {
		_uiComps.ancestors->SetState(0);
		_npcEmerged[4] = true;
	}
}

void PlayScene::__ResetGame() {
	_started = false;

	// Reset NPCs
	_uiComps.daughter->SetPosition(0, screenHeight);
	_uiComps.daughter->SetState(-1); // TODO: Debugging purpose;

	_uiComps.husband->SetPosition(0, screenHeight);
	_uiComps.husband->SetState(-1); // TODO: Debugging purpose;

	_uiComps.mother->SetPosition(0, screenHeight);
	_uiComps.mother->SetState(-1); // TODO: Debugging purpose;

	_uiComps.dancingTownspeople->SetPosition(0, screenHeight);
	_uiComps.dancingTownspeople->SetState(-1); // TODO: Debugging purpose;

	_uiComps.ancestors->SetPosition(0, screenHeight);
	_uiComps.ancestors->SetState(-1); // TODO: Debugging purpose;

	// Reset Player State
	// Game Play Initialization
	_player->SetPosition(2, 4);
	_player->ChangeTag(L"right_idle");
	_player->SetHP(_player->GetMaxHP());
	_player->SetOxygenLevel(_player->GetMaxOxyLevel());

	// Reset Bricks
	_brickGenSystem->BrickGenInit();

	// Reset UI Components
	// Attack Damage
	_uiComps.adValue->SetText(
		__WStringifyAD(_player->GetAttackDamage()).c_str()
	);
	// Combo
	_uiComps.comboValue->SetText(
		__WStringifyCombos(_player->GetCurrCombo()).c_str()
	);
	// Oxygen Level
	double oxygenRate = _player->GetCurrOxyLevel() / _player->GetMaxOxyLevel();
		_uiComps.oxygenLevel->SetY(screenHeight * (1.0 - oxygenRate));

	// Score board
	_uiComps.gloryOfFamily->SetText(__WStringifyGloryHall(_gloryOfFamilyScore).c_str());
	_uiComps.honorOfAncestor->SetText(__WStringifyMothersHonor(_mothersScore).c_str());
	_uiComps.currentHonor->SetText(__WStringifyCurrentHonor(_player->GetCurrScore()).c_str());

	// State Display
	_uiComps.currentState->SetState(
		static_cast<int>(PlayerStateAnimation::IDLE)
	);

}
