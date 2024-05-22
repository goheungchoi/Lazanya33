#include "PlayScene.h"

// Game Components
#include "GridMap.h"
#include "Player.h"
#include "Wall.h"

// Graphics
#include "SingleRenderable.h"
#include "Container.h"
#include "PlayerStateContainer.h"
#include "BlessingContainer.h"
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

constexpr int CENTERBOX_OFFSET = 718;
constexpr int RIGHTBOX_OFFSET = 660 + CENTERBOX_OFFSET;

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
	_gameEndSceneContainer = new Container(0, 0, screenWidth, screenHeight);

	// Left Box Components Allocation
	_uiComps._leftBox = new Container(0, 0, 795, screenHeight);
	// TODO: Might need to be animated
	_uiComps.daughter = new Container(0, screenHeight, 385, 465);
	_uiComps.husband = new Container(0, screenHeight, 340, 400);
	_uiComps.mother = new Container(0, screenHeight, 280, 470);;
	_uiComps.dancingTownspeople = new Container(0, screenHeight, 720, 460);
	_uiComps.ancestors = new Container(0, screenHeight, 720, 460);

	// Center Box Components Allocation
	_uiComps.levelUpSign = new Container(0, 0, 600, 200);
	_uiComps.startMessage = new Container(0, 0, 100, 36);
	_uiComps.adBox = new Container(0, 0, 200, 150);
	_uiComps.adValue = new Container(0, 0, 128, 64);
	_uiComps.comboBox = new Container(0, 0, 200, 150);
	_uiComps.comboValue = new Container(0, 0, 128, 64);

	_uiComps.oxygenMeter = new Container(0, 0, 58, screenHeight);
	_uiComps.meterBackground = new Container(0, 0, 58, screenHeight);
	_uiComps.oxygenLevel = new Container(0, 0, 58, screenHeight);

	// Right Box Components Allocation
	_uiComps._rightBox = new Container(0, 0, 809, 1080);
	_uiComps.scoreBoard = new Container(
		-5, 50, 540, 320
	);
	_uiComps.gloryOfFamily = new Container(0, 5, 530, 80);
	_uiComps.honorOfAncestor = new Container(0, 15, 530, 80);
	_uiComps.currentHonor = new Container(0, 25, 530, 80);

	// Extra Info
	_uiComps.extraInfo = new Container(-5, 50, 540, 140);
	_uiComps.additionalScore = new Container(0, 0, 270, 140);
	_uiComps.depth = new Container(0, 0, 270, 140);

	_uiComps.currentState = 
		new PlayerStateContainer(RIGHTBOX_OFFSET, screenHeight-580, 540, 580);

	// Grid Map Background
	_gridMapBackground = new SingleSpriteRenderable<GridMap>();

	_gridMap = new GridMap(
		GRID_MAP_POSITION_X, GRID_MAP_POSITION_Y,
		WALL_NUM_ROWS, WALL_NUM_COLS,
		GRID_ITEM_WIDTH, GRID_ITEM_HEIGHT
	);
	_player = new Player();
	_wall = new Wall();

	// Game End Scene Components
	_endComps.gameEndBG = new SingleSpriteRenderable<GameEndComponents>();
	_endComps.textBox = new Container(0, 0, 850, 650);
	_endComps.text1 = new Container(0, 0, 850, 120);
	_endComps.text2 = new Container(0, 0, 850, 300);
	_endComps.text3 = new Container(0, 0, 850, 120);

/********** Load Sprites **********/

	// UI Components

	_uiComps._leftBox->SetImage(ResourceManager::Get().GetImage(L"ui_left_wall"));
	_uiComps._rightBox->SetImage(ResourceManager::Get().GetImage(L"ui_right_wall"));

	_uiComps.levelUpSign->SetImage(ResourceManager::Get().GetImage(L"ui_levelup_sign"));
	_uiComps.adBox->SetImage(ResourceManager::Get().GetImage(L"ui_damage"));
	_uiComps.comboBox->SetImage(ResourceManager::Get().GetImage(L"ui_combo"));
	_uiComps.scoreBoard->SetImage(ResourceManager::Get().GetImage(L"ui_score_board"));
	_uiComps.additionalScore->SetImage(ResourceManager::Get().GetImage(L"ui_additional_score"));
	_uiComps.depth->SetImage(ResourceManager::Get().GetImage(L"ui_depth"));

	// Grid Map Background
	_gridMapBackground->BindSprite(
		ResourceManager::Get().GetImage(L"ui_tile_background")
	);
	_gridMapBackground->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"ui_tile_background")
	);

	// Player Sprite Bindings
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya1_down01"),
		L"down1"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya1_down02"),
		L"down2"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya1_Left01"),
		L"left1"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya1_Left02"),
		L"left2"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya1_Right01"),
		L"right1"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya1_Right02"),
		L"right2"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_headstone"),
		L"headstone"
	);
	_renderSystem->CachingHelper(_player);

	// Game End Background
	_endComps.gameEndBG->BindSprite(
		ResourceManager::Get().GetImage(L"game_end_background")
	);
	_endComps.gameEndBG->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"game_end_background")
	);

/********** Set UI Component Properties **********/

#ifndef NDEBUG	// Performance measure
	_fpsBox = new Container(5, 5, 100, 50);
	_fpsBox->SetFont(24, FontStyleBold);
	_fpsBox->SetText(StringifyFrameRate(0).c_str());
#endif

#ifndef NDEBUG	// _leftBox debugging borders

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
	_uiComps.adBox->EnableBorder(true);
	_uiComps.adBox->SetBorder(100, 250, 100);
	_uiComps.adValue->EnableBorder(true);
	_uiComps.adValue->SetBorder(210, 46, 120);
	_uiComps.comboBox->EnableBorder(true);
	_uiComps.comboBox->SetBorder(100, 250, 100);
	_uiComps.comboValue->EnableBorder(true);
	_uiComps.comboValue->SetBorder(210, 46, 120);

	_uiComps.scoreBoard->EnableBorder(true);
	_uiComps.scoreBoard->SetBorder(0, 0, 0, 255);
	_uiComps.gloryOfFamily->EnableBorder(true);
	_uiComps.gloryOfFamily->SetBorder(0, 220, 10);
	_uiComps.honorOfAncestor->EnableBorder(true);
	_uiComps.honorOfAncestor->SetBorder(0, 220, 90);
	_uiComps.currentHonor->EnableBorder(true);
	_uiComps.currentHonor->SetBorder(0, 220, 170);
	_uiComps.currentState->EnableBorder(true);
	_uiComps.currentState->SetBorder(0, 220, 250);
	_uiComps.extraInfo->EnableBorder(true);
	_uiComps.extraInfo->SetBorder(0, 220, 170);
	_uiComps.additionalScore->EnableBorder(true);
	_uiComps.additionalScore->SetBorder(0, 220, 10);
	_uiComps.depth->EnableBorder(true);
	_uiComps.depth->SetBorder(210, 46, 120);

	_endComps.textBox->EnableBorder(true);
	_endComps.textBox->SetBorder(255, 0, 0);
	_endComps.text1->EnableBorder(true);
	_endComps.text1->SetBorder(0, 255, 100);
	_endComps.text2->EnableBorder(true);
	_endComps.text2->SetBorder(255, 100, 20);
	_endComps.text3->EnableBorder(true);
	_endComps.text3->SetBorder(20, 0, 2550);

#endif // !NDEBUG


	// Left Box Components properties
	_uiComps._leftBox->SetPosition(0, 0);

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
	
	// LevelUp Sign
	_uiComps.levelUpSign->SetImageStrecth(false);
	_uiComps.levelUpSign->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_uiComps.levelUpSign->SetPosition(CENTERBOX_OFFSET, 200);
	
	// Start Message
	_uiComps.startMessage->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_uiComps.startMessage->SetPosition(978, 340);
	_uiComps.startMessage->SetFontFamily(L"Broadway");	// TODO: Change it to Broadway
	_uiComps.startMessage->SetFontColor(220, 220, 220, 120);
	_uiComps.startMessage->SetFont(24, FontStyleBold);
	_uiComps.startMessage->SetText(L"Press ↓");

	// Level Up Message
	_uiComps.levelUpSign->SetImageAlignment(H_DIRECTION::CENTER, V_DIRECTION::CENTER);

	// attackDamageBox?
	_uiComps.adBox->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_uiComps.adBox->SetPosition(718, 50);
	_uiComps.adBox->SetImageStrecth(false);
	_uiComps.adBox->SetImageAlignment(H_DIRECTION::CENTER, V_DIRECTION::TOP);
	_uiComps.adBox->SetDisplay(Display::FLEX);
	_uiComps.adBox->SetFlexDirection(FlexDirection::COLUMN);
	_uiComps.adBox->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_uiComps.adBox->SetFlexJustifyContent(FlexJustifyContent::SPACE_AROUND);
	_uiComps.adValue->SetPosition(
		_uiComps.adBox->GetCenterX() - (_uiComps.adValue->GetWidth() >> 1),
		_uiComps.adBox->GetCenterY() - (_uiComps.adValue->GetHeight() >> 1)
	);
	_uiComps.adValue->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.adValue->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_uiComps.adValue->SetFont(42, FontStyleBold);
	_uiComps.adValue->SetText(L"00");
	
	// comboBox
	_uiComps.comboBox->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_uiComps.comboBox->SetPosition(1118, 50);
	_uiComps.comboBox->SetImageStrecth(false);
	_uiComps.comboBox->SetImageAlignment(H_DIRECTION::CENTER, V_DIRECTION::TOP);
	_uiComps.comboBox->SetDisplay(Display::FLEX);
	_uiComps.comboBox->SetFlexDirection(FlexDirection::COLUMN);
	_uiComps.comboBox->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_uiComps.comboBox->SetFlexJustifyContent(FlexJustifyContent::SPACE_AROUND);
	_uiComps.comboValue->SetPosition(
		_uiComps.comboBox->GetCenterX() - (_uiComps.comboValue->GetWidth() >> 1),
		_uiComps.comboBox->GetCenterY() - (_uiComps.comboValue->GetHeight() >> 1)
	);
	_uiComps.comboValue->SetTextHorizontalAlignment(H_DIRECTION::CENTER);	
	_uiComps.comboValue->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.comboValue->SetFont(52, FontStyleBold);
	_uiComps.comboValue->SetText(L"00");

	// Oxygen Level
	_uiComps.oxygenMeter->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.oxygenMeter->SetPosition(600+CENTERBOX_OFFSET, 0);
	_uiComps.oxygenMeter->EnableBorder(true);
	_uiComps.oxygenMeter->SetBorder(0, 0, 0, -1, 5.f);
	_uiComps.oxygenMeter->SetZValue(10);
	_uiComps.meterBackground->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.meterBackground->SetPosition(600+CENTERBOX_OFFSET, 0);
	_uiComps.meterBackground->EnableFill(true);
	_uiComps.meterBackground->SetFillColor(255, 255, 255);
	_uiComps.oxygenLevel->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.oxygenLevel->SetPosition(600+CENTERBOX_OFFSET, 0);
	_uiComps.oxygenLevel->SetZValue(5);
	_uiComps.oxygenLevel->EnableFill(true);
	_uiComps.oxygenLevel->SetFillColor(0, 120, 240);

	// Right Box Components properties
	_uiComps._rightBox->SetPosition(RIGHTBOX_OFFSET-250, 0);
	
	_uiComps.scoreBoard->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.scoreBoard->SetPosition(RIGHTBOX_OFFSET, 0);
	_uiComps.gloryOfFamily->SetPosition(RIGHTBOX_OFFSET, 0);
	_uiComps.gloryOfFamily->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.gloryOfFamily->SetTextHorizontalAlignment(H_DIRECTION::RIGHT);
	_uiComps.gloryOfFamily->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.gloryOfFamily->SetFont(52, FontStyleBold);
	
	_uiComps.honorOfAncestor->SetPosition(RIGHTBOX_OFFSET, 100);
	_uiComps.honorOfAncestor->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.honorOfAncestor->SetTextHorizontalAlignment(H_DIRECTION::RIGHT);
	_uiComps.honorOfAncestor->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.honorOfAncestor->SetFont(52, FontStyleBold);

	_uiComps.currentHonor->SetPosition(RIGHTBOX_OFFSET, 200);
	_uiComps.currentHonor->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.currentHonor->SetTextHorizontalAlignment(H_DIRECTION::RIGHT);
	_uiComps.currentHonor->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.currentHonor->SetFont(52, FontStyleBold);

	_uiComps.extraInfo->SetPosition(RIGHTBOX_OFFSET, 320);
	_uiComps.extraInfo->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_uiComps.extraInfo->SetDisplay(Display::FLEX);
	_uiComps.extraInfo->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_uiComps.extraInfo->SetFlexJustifyContent(FlexJustifyContent::SPACE_BETWEEN);

	_uiComps.additionalScore->SetPosition(RIGHTBOX_OFFSET, 320);
	_uiComps.additionalScore->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.additionalScore->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.additionalScore->SetFont(52, FontStyleBold);
	_uiComps.additionalScore->SetText(L"00");	// DEBUG

	_uiComps.depth->SetPosition(RIGHTBOX_OFFSET+280, 320);
	_uiComps.depth->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.depth->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.depth->SetFont(52, FontStyleBold);
	_uiComps.depth->SetText(L"00 M");	// DEBUG

	
	// Add Animations in the currentState.
	_uiComps.currentState->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);


	// The UI Container
	_gamePlayUIContainer->SetDisplay(Display::FLEX);
	_gamePlayUIContainer->SetFlexJustifyContent(FlexJustifyContent::FLEX_START);

	_gridMapBackground->SetPosition(CENTERBOX_OFFSET, 0);


	// The Game End Components
	// Background
	_endComps.gameEndBG->SetPosition(screenWidth >> 1, screenHeight >> 1);
	_endComps.gameEndBG->UpdateSpritePivotPosition(H_DIRECTION::CENTER, V_DIRECTION::CENTER);
	
	_gameEndSceneContainer->SetDisplay(Display::FLEX);
	_gameEndSceneContainer->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_gameEndSceneContainer->SetFlexJustifyContent(FlexJustifyContent::FLEX_CENTER);
	
	_endComps.textBox->SetPositionLayout(PositionLayout::LAYOUT_RELATIVE);
	_endComps.textBox->SetRotationPivot(screenWidth >> 1, screenHeight >> 1);
	_endComps.textBox->Translate(100, -100);
	_endComps.textBox->Rotate(-8);
	_endComps.textBox->SetDisplay(Display::FLEX);
	_endComps.textBox->SetFlexDirection(FlexDirection::COLUMN);
	_endComps.textBox->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_endComps.textBox->SetFlexJustifyContent(FlexJustifyContent::SPACE_AROUND);

	_endComps.text1->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_endComps.text1->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_endComps.text1->SetFont(36, FontStyleBold);
	_endComps.text2->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_endComps.text2->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_endComps.text2->SetFont(36, FontStyleBold);
	_endComps.text3->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_endComps.text3->SetTextVerticalJustify(V_DIRECTION::CENTER);
	_endComps.text3->SetFont(36, FontStyleBold);

/********** Build UI Hierarchy **********/

	// Left Box Components
	_uiComps._leftBox->AddChildComponent(_uiComps.daughter);
	_uiComps._leftBox->AddChildComponent(_uiComps.husband);
	_uiComps._leftBox->AddChildComponent(_uiComps.mother);
	_uiComps._leftBox->AddChildComponent(_uiComps.dancingTownspeople);
	_uiComps._leftBox->AddChildComponent(_uiComps.ancestors);

	_uiComps._rightBox->AddChildComponent(_uiComps.scoreBoard);
	_uiComps._rightBox->AddChildComponent(_uiComps.gloryOfFamily);
	_uiComps._rightBox->AddChildComponent(_uiComps.honorOfAncestor);
	_uiComps._rightBox->AddChildComponent(_uiComps.currentHonor);
	_uiComps._rightBox->AddChildComponent(_uiComps.extraInfo);
	_uiComps._rightBox->AddChildComponent(_uiComps.additionalScore);
	_uiComps._rightBox->AddChildComponent(_uiComps.depth);
	_uiComps._rightBox->AddChildComponent(_uiComps.currentState);


	// Bind Player and Wall to GridMap
	_gridMap->AddGridItem(_wall);
	_gridMap->AddGridItem(_player);

	//// UI Container binding
	
	_gamePlayUIContainer->AddChildComponent(_uiComps.levelUpSign);
	_gamePlayUIContainer->AddChildComponent(_uiComps.startMessage);
	_gamePlayUIContainer->AddChildComponent(_uiComps.adBox);
	_gamePlayUIContainer->AddChildComponent(_uiComps.adValue);
	_gamePlayUIContainer->AddChildComponent(_uiComps.comboBox);
	_gamePlayUIContainer->AddChildComponent(_uiComps.comboValue);
	_gamePlayUIContainer->AddChildComponent(_uiComps.oxygenMeter);
	_gamePlayUIContainer->AddChildComponent(_uiComps.meterBackground);
	_gamePlayUIContainer->AddChildComponent(_uiComps.oxygenLevel);
	
	_gamePlayUIContainer->AddChildComponent(_uiComps._leftBox);
	_gamePlayUIContainer->AddChildComponent(_uiComps._rightBox);
	
	// Game End Components
	//_endComps.textBox->AddChildComponent(_endComps.text1);
	//_endComps.textBox->AddChildComponent(_endComps.text2);
	//_endComps.textBox->AddChildComponent(_endComps.text3);

	//_gameEndSceneContainer->AddChildComponent(_endComps.textBox);

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
#endif

	if (_started) {
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

		// Update 
		_uiComps.honorOfAncestor->SetText(
			__WStringifyMothersHonor(GetGameDataHub().GetMaxScore()).c_str()
		);
		_uiComps.honorOfAncestor->SetText(
			__WStringifyMothersHonor(GetGameDataHub().GetPreviousUser().score).c_str()
		);
		_uiComps.currentHonor->SetText(
			__WStringifyCurrentHonor(_player->GetCurrScore()).c_str()
		);

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

		// Update Additional Score
		_uiComps.additionalScore->SetText(
			__WStringifyCombos(0).c_str()
		);

		// Update Depth
		_uiComps.depth->SetText(
			__WStringifyDepth(_player->GetDownMeter()).c_str()
		);

		// TODO: Update Level Up Sign!!!

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
		
		// Dead image
		_player->GetPlayer()->ChangeTag(L"headstone");

		// Set State image
		_uiComps.currentState->SetState(
			static_cast<int>(PlayerStateAnimation::DEAD)
		);

		// Show pop up windows
		if (!_ended) {
			_delayEnding += deltaTime;
			if (_delayEnding > 3) {
				_endComps.gameEndBG->SetActive(true);
				_gameEndSceneContainer->SetActive(true);

				TextAnimation* txt1 = new TextAnimation(
					_endComps.text1,
					__WStringifyEndingMessage1().c_str(),
					2.0, 1.0
				);

				TextAnimation* txt2;
				int playerScore = _player->GetCurrScore();
				if (
					playerScore > GetGameDataHub().GetMaxScore() &&
					playerScore > 100
				) {
					txt2 = new TextAnimation(
						_endComps.text2,
						__WStringifyEndingMessage2_3().c_str(),
						3.0, 1.0
					);
				}
				else if (
					playerScore > GetGameDataHub().GetPreviousUser().score &&
					playerScore > 60
				) {
					txt2 = new TextAnimation(
						_endComps.text2,
						__WStringifyEndingMessage2_2().c_str(),
						2.0, 1.0
					);
				}
				else {
					txt2 = new TextAnimation(
						_endComps.text2,
						__WStringifyEndingMessage2_1().c_str(),
						1.0, 1.0
					);
				}

				TextAnimation* txt3 = new TextAnimation(
					_endComps.text3,
					__WStringifyEndingMessage3().c_str(),
					2.0, 1.0
				);

				SequentialAnimationPack* sanim = new SequentialAnimationPack();
				sanim->PushBackAnimation(txt1);
				sanim->PushBackAnimation(txt2);
				sanim->PushBackAnimation(txt3);

				_endComps.text1->AddAnimation(0, sanim);
				_endComps.text1->SetState(0);

				_ended = true;
			}
		}

		_endComps.text1->Update(deltaTime);

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
	// DEBUG: 
	//_player->SetOxygenLevel(0);


	// RenderSystem Registration
	// Rendering order of the GamePlay scene
	// 1. Background
	// 2. Grid Map
	// 2. GamePlay UI components
	_renderSystem->RegisterRenderableObject(_gridMapBackground);
	_renderSystem->RegisterRenderableObject(_gridMap);
	_renderSystem->RegisterRenderableObject(_gamePlayUIContainer);
	
	_renderSystem->RegisterRenderableObject(_endComps.gameEndBG);
	_renderSystem->RegisterRenderableObject(_gameEndSceneContainer);

#ifndef NDEBUG	// Performance measure
	_renderSystem->RegisterRenderableObject(_fpsBox);
#endif

	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::BackGround02, Music::eSoundChannel::BGM);
}

void PlayScene::EndScene()
{
	_renderSystem->ClearRenderableRegistry();
}

void PlayScene::__PlayerUpdate(const double deltaTime)
{
	_player->GetPlayer()->Update(deltaTime);
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


		_player->GetPlayer()->TriggerEffect(PlayerEffect::DOWN_ATTACK);
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY() + 1, _player->GetPositionX(),
			VK_DOWN, _countWallPop, deltaTime
		);

		if (_player->IsFacingLeft())
			_player->GetPlayer()->ChangeTag(L"left_attack");
		else
			_player->GetPlayer()->ChangeTag(L"right_attack");

		++_buttonPressedCount;
	}

	// DOWN arrow key up
	if (Input::inputManager->IsTurnUp(VK_DOWN)) {
		if (_player->IsFacingLeft())
			_player->GetPlayer()->ChangeTag(L"left_idle");
		else
			_player->GetPlayer()->ChangeTag(L"right_idle");
	}

	// LEFT arrow key is pressed
	if (Input::inputManager->IsTurnDn(VK_LEFT) && 
		_player->GetPositionX() > 0 && 
		_wall->GetBrick(_player->GetPositionY(), _player->GetPositionX() - 1).type
		!= BrickType::NONE) {
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Effect);

		// Play the left attack effect
		_player->GetPlayer()->TriggerEffect(PlayerEffect::LEFT_ATTACK);

		// Change the player pose
		_player->GetPlayer()->ChangeTag(L"left_attack");
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
		_player->GetPlayer()->ChangeTag(L"left_move");
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
		_player->GetPlayer()->TriggerEffect(PlayerEffect::RIGHT_ATTACK);

		// Change the player pose
		_player->GetPlayer()->ChangeTag(L"right_attack");
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
		_player->GetPlayer()->ChangeTag(L"right_move");
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
	_player = _player->GetPlayer();
	// Game Play Initialization
	_player->SetPosition(2, 4);
	_player->ChangeTag(L"right_idle");
	_player->SetHP(_player->GetMaxHP());
	_player->SetOxygenLevel(_player->GetMaxOxyLevel());
	// Set Decorator
	BlessingType blessingType = static_cast<BlessingType>(
		GetGameDataHub().GetCurrentUserBlessIndex()
	);
	switch (blessingType)
	{
	case BlessingType::Virago:
		break;
	case BlessingType::Anaerobic:
		_player = new Anaerobic(_player);
		break;
	case BlessingType::GoldSeeker:
		_player = new GoldSeeker(_player);
		break;
	case BlessingType::Naughty:
		_player = new Naughty(_player);
		break;
	case BlessingType::Pummeler:
		_player = new Pummeler(_player);
		break;
	case BlessingType::SugarGirl:
		_player = new SugarGirl(_player);
		break;
	case BlessingType::TenaciousDwarf:
		_player = new TenaciousDwarf(_player);
		break;
	case BlessingType::Wimp:
		_player = new Wimp(_player);
		break;
	default:
		break;
	}

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

	// Turn off Game End Components
	_gameEndSceneContainer->SetActive(false);
	_endComps.gameEndBG->SetActive(false);

	// Change Systems.
	__InitSystems();
}


std::wstring PlayScene::__WStringifyEndingMessage1() {
	wchar_t buffer[50];
	swprintf_s(buffer, 
		L"-라자냐+ [-%d+]세,\n"
		L"무스티니 동굴 [-%d+]에서 잠들다.", 
		GetGameDataHub().GetCurrentGeneration(),
		_player->GetDownMeter()
	);
	return std::wstring(buffer);
}

std::wstring PlayScene::__WStringifyEndingMessage2_1() {
	wchar_t buffer[50];
	swprintf_s(buffer, 
		L"그녀의 활약은 [-%d+] 만큼 훌륭했으며,\n",
		_player->GetCurrScore()
	);
	return std::wstring(buffer);
}
std::wstring PlayScene::__WStringifyEndingMessage2_2() {
	wchar_t buffer[50];
	swprintf_s(buffer, 
		L"그녀의 활약은 [-%d+] 만큼 훌륭했으며,\n"
		L"그녀의 어머니를 능가했고,\n",
		_player->GetCurrScore()
	);
	return std::wstring(buffer);
}
std::wstring PlayScene::__WStringifyEndingMessage2_3() {
	wchar_t buffer[50];
	swprintf_s(buffer, 
		L"그녀의 활약은 [-%d+] 만큼 훌륭했으며,\n"
		L"그녀의 어머니를 능가했고,\n",
		L"가문의 영광이 되었다.\n",
		_player->GetCurrScore()
	);
	return std::wstring(buffer);
}
	
std::wstring PlayScene::__WStringifyEndingMessage3() {
	wchar_t buffer[50];
	swprintf_s(buffer, 
		L"그녀의 후손 라자냐 [-%d+]세가,\n"
		L"뒤를 따를 것이다.", 
		GetGameDataHub().GetCurrentGeneration() + 1
	);
	return std::wstring(buffer);
}
