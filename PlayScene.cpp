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

	_buttonEventHandler = new ButtonEventHandler();
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
	_uiComps.startMessage = new Container(0, 0, 130, 36);
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
	_endComps.text1 = new Container(580, 300, 850, 120);
	_endComps.text2 = new Container(700, 400, 750, 300);
	_endComps.text3 = new Container(650, 700, 850, 120);
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

	_player->BindImage(
		ResourceManager::Get().GetImage(L"lazanya_ingame_headstone"),
		L"headstone"
	);
	_player->SetCaching(false);

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

	_uiComps.husband->SetSizeFitImage(true);
	_uiComps.husband->SetImage(
		ResourceManager::Get().GetImage(L"70000_NPC_husband_bigger")
	);
	_uiComps.daughter->SetSizeFitImage(true);
	_uiComps.daughter->SetImage(
		ResourceManager::Get().GetImage(L"70001_NPC_daugh_bigger")
	);
	_uiComps.mother->SetSizeFitImage(true);
	_uiComps.mother->SetImage(
		ResourceManager::Get().GetImage(L"70002_NPC_mother_bigger")
	);
	_uiComps.dancingTownspeople->SetSizeFitImage(true);
	_uiComps.dancingTownspeople->SetImage(
		ResourceManager::Get().GetImage(L"70003_NPC_villagers_final")
	);
	_uiComps.ancestors->SetSizeFitImage(true);
	_uiComps.ancestors->SetImage(
		ResourceManager::Get().GetImage(L"70004_NPC_ancestors")
	);

	_endComps.text1->SetFontFamilyByPath(L"가평한석봉 큰붓 B", L"Font/GapyeongHanseokbongB.ttf");
  _endComps.text1->SetRotationPivot(
	_endComps.text1->GetCenterX(),
  _endComps.text1->GetCenterY());
  _endComps.text1->Rotate(-7);
	
	_endComps.text2->SetFontFamilyByPath(L"가평한석봉 큰붓 B", L"Font/GapyeongHanseokbongB.ttf");
  _endComps.text2->SetRotationPivot(
	_endComps.text2->GetCenterX(),                             
	_endComps.text2->GetCenterY());
  _endComps.text2->Rotate(-7);

	_endComps.text3->SetFontFamilyByPath(L"가평한석봉 큰붓 B", L"Font/GapyeongHanseokbongB.ttf");
  _endComps.text3->SetRotationPivot(
	_endComps.text3->GetCenterX(),
  _endComps.text3->GetCenterY());
  _endComps.text3->Rotate(-7);

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
		0, 300, 30, 700, 0.3, bezier::ease_in
	);
	IAnimation* daughter_moveup = new TranslateTransition(
		_uiComps.daughter,
		10, 700, 10, 500, 0.3, bezier::ease_out
	);
	IAnimation* daughter_movedown = new TranslateTransition(
		_uiComps.daughter,
		10, 500, 10, 700, 0.3, bezier::ease_in
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
		160, 100, 290, 615, 0.3, bezier::ease_in
	);
	IAnimation* husband_moveup = new TranslateTransition(
		_uiComps.husband,
		290, 615, 290, 400, 0.3, bezier::ease_out
	);
	IAnimation* husband_movedown = new TranslateTransition(
		_uiComps.husband,
		290, 400, 290, 615, 0.3, bezier::ease_in
	);
	SequentialAnimationPack* husband_animationPack = new SequentialAnimationPack();
	husband_animationPack->PushBackAnimation(
		{ husband_shootup, husband_comedown, husband_moveup, husband_movedown }
	);
	husband_animationPack->SetLoop(true);
	husband_animationPack->SetLoopRange(2, 4);
	_uiComps.husband->AddAnimation(0, husband_animationPack);

	// Mother
	_uiComps.mother->SetZValue(9);
	_uiComps.mother->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.mother->SetPosition(0, screenHeight);
	// Mother pop-up animation
	IAnimation* mother_shootup = new TranslateTransition(
		_uiComps.mother,
		500, screenHeight-100, 250, 100, 0.5, bezier::ease_out
	);
	IAnimation* mother_comedown = new TranslateTransition(
		_uiComps.mother,
		250, 100, 125, 580, 0.3, bezier::ease_in
	);
	IAnimation* mother_moveup = new TranslateTransition(
		_uiComps.mother,
		125, 580, 125, 380, 0.3, bezier::ease_out
	);
	IAnimation* mother_movedown = new TranslateTransition(
		_uiComps.mother,
		125, 380, 125, 580, 0.3, bezier::ease_in
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
		0, -100, 0, 250, 0.3, bezier::ease_in
	);
	IAnimation* dancingTownspeople_moveup = new TranslateTransition(
		_uiComps.dancingTownspeople,
		0, 250, 0, 120, 0.3, bezier::ease_out
	);
	IAnimation* dancingTownspeople_movedown = new TranslateTransition(
		_uiComps.dancingTownspeople,
		0, 120, 0, 250, 0.3, bezier::ease_in
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
	_uiComps.levelUpSign->SetActive(false);
	_uiComps.levelUpSign->SetImageStrecth(false);
	_uiComps.levelUpSign->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_uiComps.levelUpSign->SetPosition(CENTERBOX_OFFSET, 200);
	
	// Start Message
	_uiComps.startMessage->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_uiComps.startMessage->SetPosition(955, 330);
	_uiComps.startMessage->SetTextHorizontalAlignment(H_DIRECTION::CENTER);
	_uiComps.startMessage->SetFontFamilyByPath(L"Threat", L"Font/Threat.otf");
	_uiComps.startMessage->SetFontColor(220, 220, 220, 120);
	_uiComps.startMessage->SetFont(24, FontStyleBold);
	_uiComps.startMessage->SetText(L"PRESS ↓");

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
	_uiComps.adValue->SetTextHorizontalAlignment(H_DIRECTION::LEFT);
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
	_uiComps.comboEffect = new Animation(
		ResourceManager::Get().GetImage(L"combo_fire_effect"),
		_uiComps.comboBox->GetX()+55, _uiComps.comboBox->GetY()-20, true
	);
	_uiComps.comboEffect->SliceSpriteSheet(160, 160, 0, 0, 0, 0);
	_uiComps.comboEffect->SetFrameDurations({ 0.01 });
	_uiComps.comboBox->AddAnimation(0, _uiComps.comboEffect);

	_uiComps.comboValue->SetPosition(	// Center position
		_uiComps.comboBox->GetCenterX() - (_uiComps.comboValue->GetWidth() >> 1),
		_uiComps.comboBox->GetCenterY() - (_uiComps.comboValue->GetHeight() >> 1) + 5
	);
	_uiComps.textShake = new TranslateTransition(
		_uiComps.comboValue,
		_uiComps.comboValue->GetX(), _uiComps.comboValue->GetY()-10,
		_uiComps.comboValue->GetX(), _uiComps.comboValue->GetY(),
		0.5, bezier::linear
	);
	_uiComps.comboValue->AddAnimation(0, _uiComps.textShake);

	

	_uiComps.comboValue->SetTextHorizontalAlignment(H_DIRECTION::RIGHT);	
	_uiComps.comboValue->SetTextVerticalJustify(V_DIRECTION::BOTTOM);
	_uiComps.comboValue->SetFontColor(255, 0, 0);
	_uiComps.comboValue->SetFont(52, FontStyleBold);
	_uiComps.comboValue->SetText(L"00");

	// Oxygen Level
	_uiComps.oxygenMeter->SetPosition(600+CENTERBOX_OFFSET, 0);
	_uiComps.oxygenMeter->EnableBorder(true);
	_uiComps.oxygenMeter->SetBorder(0, 0, 0, -1, 5.f);
	_uiComps.oxygenMeter->SetZValue(10);
	_uiComps.meterBackground->SetPosition(600+CENTERBOX_OFFSET, 0);
	_uiComps.meterBackground->EnableFill(true);
	_uiComps.meterBackground->SetZValue(8);
	_uiComps.meterBackground->SetFillColor(255, 255, 255);
	_uiComps.oxygenLevel->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_uiComps.oxygenLevel->SetPosition(600+CENTERBOX_OFFSET, 0);
	_uiComps.oxygenLevel->SetZValue(9);
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
	_endComps.textBox->AddChildComponent(_endComps.text1);
	_endComps.textBox->AddChildComponent(_endComps.text2);
	_endComps.textBox->AddChildComponent(_endComps.text3);

	_gameEndSceneContainer->AddChildComponent(_endComps.textBox);




	_endComps.gotohistory = new Button(950, 850, 200, 200);
	_endComps.gotohistory->SetSizeFitImage(true);
	_endComps.gotohistory->SetImage(
		ResourceManager::Get().GetImage(L"30011_UI_Game_Over_History01_Button")
	);
	_endComps.gotohistory->SetRotationPivot(
		_endComps.gotohistory->GetCenterX(),
		_endComps.gotohistory->GetCenterY()
	);
	_endComps.gotohistory->Rotate(-7);

	_endComps.gotohistory->AddEventLister("mouseEnter", [this]() {
		_endComps.gotohistory->SetImageIntensity(2.0f);
		});
	_endComps.gotohistory->AddEventLister("mouseLeave", [this]() {
		_endComps.gotohistory->SetImageIntensity(1 / 2.0f);
		});

	_endComps.gotohistory->AddEventLister("mouseClick", [this]() {
		if (_delayEnding > 3)
		{
			Music::soundManager->PlayMusic(Music::eSoundList::PaperSwap, Music::eSoundChannel::Effect);
			_canGohistory = true;
			_historyComps.historyBG->SetActive(true);
			_historyComps.entryButton->SetActive(true);
			_historyContainer->SetActive(true);
		}
		});
	_buttonEventHandler->AddButton(_endComps.gotohistory);
	_gameEndSceneContainer->AddChildComponent(_endComps.gotohistory);



	//history componenet
	_historyContainer = new Container(0, 0, screenWidth, screenHeight);
	_historyComps.historyBG = new SingleSpriteRenderable<HistoryComponents>();
	_historyComps.historyBG->BindSprite(
		ResourceManager::Get().GetImage(L"30012_UI_Game_Over_History02")
	);
	_historyComps.historyBG->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"30012_UI_Game_Over_History02")
	);
	
	//name
	_historyComps.name = new TextInputField(860, 680, 100, 100);
	_historyComps.name->SetZValue(8);
	_historyContainer->AddChildComponent(_historyComps.name);
	//nametag
	_historyComps.nameTag = new Container(740, 650, 100, 100);
	_historyComps.nameTag->SetSizeFitImage(true);
	_historyComps.nameTag->SetImage(
		ResourceManager::Get().GetImage(L"30013_UI_Game_Over_History02_Name")
	);
	_historyComps.nameTag->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_historyContainer->AddChildComponent(_historyComps.nameTag);
	//button
	_historyComps.entryButton = new Button(1100, 820, 100, 100);
	_historyComps.entryButton->SetSizeFitImage(true);
	_historyComps.entryButton->SetImage(
		ResourceManager::Get().GetImage(L"30014_UI_Game_Over_History02_Button")
	);
	_historyComps.entryButton->AddEventLister("mouseEnter", [this]() {
		_historyComps.entryButton->SetImageIntensity(2.0f);
		});
	_historyComps.entryButton->AddEventLister("mouseLeave", [this]() {
		_historyComps.entryButton->SetImageIntensity(1 / 2.0f);
		});
	_historyComps.entryButton->AddEventLister("mouseClick", [this]() {
		_delayEnding = 0.0;
		_wall->ResetWalls(_countWallPop);
		_countWallPop = 0;
		_player->SetDownMeter(0);
		_uiComps.depth->SetText(L"00 M");
		_sceneManager->ChangeScene("Entry");
		
		});
	
	_buttonEventHandler->AddButton(_historyComps.entryButton);
	_historyContainer->AddChildComponent(_historyComps.entryButton);

	//text
	_historyComps.text = new Container(630, 420, 1000, 200);
	_historyComps.text->SetFontFamilyByPath(L"가평한석봉 큰붓 B", L"Font/GapyeongHanseokbongB.ttf");
	_historyComps.text->SetFont(100, FontStyleBold);
	_historyComps.text->SetFontColor(255, 255, 255);
	_historyComps.text->SetText(L"당신의 이니셜은?");
	_historyComps.name->SetPositionLayout(PositionLayout::LAYOUT_ABSOLUTE);
	_historyComps.name->SetFont(40, FontStyleBold);
	_historyContainer->AddChildComponent(_historyComps.text);
}

void PlayScene::__InitSystems() {
	if (_brickGenSystem == nullptr)
		_brickGenSystem = new BrickGenSystem(_wall, _player);
	else
		_brickGenSystem->SetIPlayer(_player);

	if (_playerOxySystem == nullptr)
		_playerOxySystem = new PlayerOxygenSystem(
			_player, PLAYER_OXYGEN_REDUCE_INITAL_VALUE
		);
	else
		_playerOxySystem->SetIPlayer(_player);

	if (_playerBrickInteractionSystem == nullptr)
		_playerBrickInteractionSystem = new PlayerBricksInteractionSystem(
			_player, _wall, _playerOxySystem
		);
	else
		_playerBrickInteractionSystem->SetIPlayer(_player);
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

	_wall->Update(deltaTime);

	if (_started) {
		// Update player
		__PlayerUpdate(deltaTime);
		__AutoValveCondition([this]() {
			return _player->GetDownMeter() >= _nextLevelUpCeiling;
		});

		// Update Level Up Animation
		LevelUpAnimationUpdate(deltaTime);

		// Trigger NPC animation if any condition meets;
		__TriggerNPCsAnimations();

		// Update NPCs
		_uiComps.daughter->Update(deltaTime);
		_uiComps.husband->Update(deltaTime);
		_uiComps.mother->Update(deltaTime);
		_uiComps.dancingTownspeople->Update(deltaTime);
		_uiComps.ancestors->Update(deltaTime);

		// Update 
		_uiComps.gloryOfFamily->SetText(
			__WStringifyGloryHall(
				_gloryOfFamilyScore < _player->GetCurrScore() ?
				_player->GetCurrScore() : _gloryOfFamilyScore
			).c_str()
		);
		_uiComps.honorOfAncestor->SetText(
			__WStringifyMothersHonor(_mothersScore).c_str()
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

		// Update Combo Animation
		_uiComps.comboBox->Update(deltaTime);
		_uiComps.comboValue->Update(deltaTime);
		
		if (_player->NotifyComboChange()) {
			_uiComps.textShake->Trigger();
			_uiComps.comboValue->SetState(0);
		}

		if (_player->GetCurrCombo() < 5) {
			_uiComps.comboBox->SetState(-1);
		} else {
			_uiComps.comboBox->SetState(0);
		}

		if (_player->GetCurrCombo() == 5&&!_fiveComboSound) {
			Music::soundManager->PlayMusic(Music::eSoundList::FiveCombo, Music::eSoundChannel::Combo);
			_fiveComboSound = true;
		}

		// Update Additional Score
		_uiComps.additionalScore->SetText(
			[this, currCombo = _player->GetCurrCombo()]() -> std::wstring {
				switch (currCombo) {
				case 0:
				case 1:
					return __WStringifyCombos(0);
				case 2:
					return __WStringifyCombos(1);
				case 3:
					return __WStringifyCombos(2);
				case 4:
					return __WStringifyCombos(3);
				case 5:
				default:
					return __WStringifyCombos(4);
				}
			}().c_str()
		);

		// Update Depth
		_uiComps.depth->SetText(
			__WStringifyDepth(_player->GetDownMeter()).c_str()
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
		
		// Dead image
		_player->GetPlayer()->ChangeTag(L"headstone");

		// Set State image
		_uiComps.currentState->SetState(
			static_cast<int>(PlayerStateAnimation::DEAD)
		);
		_buttonEventHandler->HandleMouseEvent(
			Input::inputManager->GetMouseClient().x,
			Input::inputManager->GetMouseClient().y,
			Input::inputManager->IsCurrDn(VK_LBUTTON),
			Input::inputManager->IsCurrUp(VK_LBUTTON)
		);

		if (_canGohistory == true)
		{
			for (int i = 0; i < 256; i++)
			{
				if (Input::inputManager->IsTurnDn(i))
				{
					if (i >= 'A' && i <= 'Z'&&_historyComps
						.name->text.length()<6)
					{
						_historyComps.name->text.push_back(i);
						_historyComps.name->text.push_back(' ');
						if(_typingCount==0)
							Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type1);
						else if(_typingCount==1)
							Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type2);
						else if(_typingCount==2)
							Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type3);
						_typingCount++;
					}
					else if (i == 8 && !_historyComps.name->text.empty())
					{
						_historyComps.name->text.pop_back();
						_historyComps.name->text.pop_back();
						if (_typingCount == 0)
							Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type1);
						else if (_typingCount == 1)
							Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type2);
						else if (_typingCount == 2)
							Music::soundManager->PlayMusic(Music::eSoundList::TypeName, Music::eSoundChannel::Type3);
						_typingCount--;
					}
					else
						continue;
				}
			}
			_historyComps.entryButton->SetActive(_historyComps.name->text.length() > 0);
		}

		// Show pop up windows
		if (!_ended) {

			if (!_playDeathSound)
			{
				Music::soundManager->PlayMusic(Music::eSoundList::death, Music::eSoundChannel::Death);
				_playDeathSound = true;
			}
			// Ending delay 3 seconds
			_delayEnding += deltaTime;
			if (_delayEnding > 3) {

				_endComps.gameEndBG->SetActive(true);
				_endComps.gotohistory->SetActive(true);
				_gameEndSceneContainer->SetActive(true);

				txt1 = new TextAnimation(
					_endComps.text1,
					__WStringifyEndingMessage1().c_str(),
					1.0, 1.0
				);

				int playerScore = _player->GetCurrScore();
				if (playerScore > _gloryOfFamilyScore) {
					txt2 = new TextAnimation(
						_endComps.text2,
						__WStringifyEndingMessage2_3().c_str(),
						1.5, 1.0
					);
				}
				else if (playerScore > _mothersScore) {
					txt2 = new TextAnimation(
						_endComps.text2,
						__WStringifyEndingMessage2_2().c_str(),
						1.0, 1.0
					);
				}
				else {
					txt2 = new TextAnimation(
						_endComps.text2,
						__WStringifyEndingMessage2_1().c_str(),
						0.5, 1.0
					);
				}

				txt3 = new TextAnimation(
					_endComps.text3,
					__WStringifyEndingMessage3().c_str(),
					1.0, 1.0
				);

				sanim = new SequentialAnimationPack();
				sanim->PushBackAnimation(txt1);
				sanim->PushBackAnimation(txt2);
				sanim->PushBackAnimation(txt3);

				_endComps.text1->AddAnimation(0, sanim);
				_endComps.text1->SetState(0);

				_ended = true;
				_playDeathSound = false;
				
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

	_renderSystem->RegisterRenderableObject(_historyComps.historyBG);
	_renderSystem->RegisterRenderableObject(_historyContainer);
#ifndef NDEBUG	// Performance measure
	_renderSystem->RegisterRenderableObject(_fpsBox);
#endif

	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::BackGround02, Music::eSoundChannel::BGM);
}

void PlayScene::EndScene()
{
	sanim->Reset();
	_endComps.text1->SetText(L"");
	_endComps.text2->SetText(L"");
	_endComps.text3->SetText(L"");
	_renderSystem->ClearRenderableRegistry();

	GetGameDataHub().SetCurrentUserName(_historyComps.name->text.c_str());
	GetGameDataHub().SetCurrentUserDepth(_player->GetDownMeter());
	GetGameDataHub().SetCurrentUserScore(_player->GetCurrScore());
	GetGameDataHub().DispatchCurrentUserData();
	Music::soundManager->PlayMusic(Music::eSoundList::background01, Music::eSoundChannel::BGM);
}

void PlayScene::__PlayerUpdate(const double deltaTime)
{
	_player->Update(deltaTime);
	//comboDuration++
	_player->AddComboElapsedTime(deltaTime);

	//Set to combo 0 every ComboDuration second
	if (_player->GetComboElapsedTime() >= _player->GetComboDuration())
	{
		_reverseArrowKeys ? _player->SetCombo(2) : _player->SetCombo(0);
		_player->AddComboElapsedTime(-1);
		_fiveComboSound = false;
	}

	// Set combo 99 if over 100
	if (_player->GetCurrCombo() >= 100) {
		_player->SetCombo(99);
	}

	// DOWN arrow key pressed
	if (Input::inputManager->IsTurnDn(VK_DOWN))
	{
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Attack);
		_player->DownKeyPressed();

		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY() + 1, _player->GetPositionX(),
			VK_DOWN, _countWallPop, deltaTime
		);

		if (!_player->GetDownBool())
			_player->GetPlayer()->ChangeTag(L"down1");
		else
			_player->GetPlayer()->ChangeTag(L"down2");

		++_buttonPressedCount;
	}

	// LEFT arrow key is pressed
	if (Input::inputManager->IsTurnDn(_reverseArrowKeys ? VK_RIGHT : VK_LEFT) && 
		_player->GetPositionX() > 0 && 
		_wall->GetBrick(
			_player->GetPositionY(), 
			_player->GetPositionX() - 1
		).type != BrickType::NONE) {
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Attack);
		_player->LeftKeyPressed();

		// Change the player pose
		if (!_player->GetLeftBool())
			_player->GetPlayer()->ChangeTag(L"left1");
		else
			_player->GetPlayer()->ChangeTag(L"left2");

		// Damage Brick
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY(), 
			_player->GetPositionX() - 1,
			VK_LEFT, _countWallPop, deltaTime
		);

		++_buttonPressedCount;
	}
	
	// RIGHT arrow key is pressed
	if (Input::inputManager->IsTurnDn(_reverseArrowKeys ? VK_LEFT : VK_RIGHT) &&
		_player->GetPositionX() < 4 &&
		_wall->GetBrick(
			_player->GetPositionY(),
			_player->GetPositionX() + 1
		).type != BrickType::NONE) {
		Music::soundManager->PlayMusic(Music::eSoundList::Attack, Music::eSoundChannel::Attack);
		_player->RightKeyPressed();
		
		// Change the player pose
		if (!_player->GetRightBool())
			_player->GetPlayer()->ChangeTag(L"right1");
		else
			_player->GetPlayer()->ChangeTag(L"right2");

		// Damage Brick
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer(
			_player->GetPositionY(),
			_player->GetPositionX() + 1,
			VK_RIGHT, _countWallPop, deltaTime
		);

		++_buttonPressedCount;
	}
	
	//if pop wall three time
	if (_countWallPop == 3)
	{
		_brickGenSystem->GenerateNextRows();
		_countWallPop = 0;
	}

	//player oxygen system
	_playerOxySystem->ReduceOxygen(deltaTime);

	// Lasgula Update
	if (_player->GetCurrOxyLevel() <= 0 &&
		_player->IsLasgula()) {
		_player->ResetLasgulaChanges();
	}
	_player->UpdateLasgulaState(deltaTime);

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
		Music::soundManager->PlayMusic(Music::eSoundList::mother, Music::eSoundChannel::Mother);
		_uiComps.mother->SetState(0);
		_npcEmerged[3] = true;
	}
	if (!_npcEmerged[4] && 
		_player->GetCurrScore() >= _gloryOfFamilyScore) {
		Music::soundManager->PlayMusic(Music::eSoundList::bestScore, Music::eSoundChannel::Acient);
		_uiComps.ancestors->SetState(0);
		_npcEmerged[4] = true;
	}
}

void PlayScene::__ResetGame() {
	
	_typingCount = 0;
	// Reset states
	_reverseArrowKeys = false;
	_started = false;
	_ended = false;
	_canGohistory = false;

	// Reset NPCs
	_npcEmerged[0] = false;
	_uiComps.daughter->ResetAnimation();
	_uiComps.daughter->SetPosition(0, screenHeight);
	_uiComps.daughter->SetState(-1); // TODO: Debugging purpose;

	_npcEmerged[1] = false;
	_uiComps.husband->ResetAnimation();
	_uiComps.husband->SetPosition(0, screenHeight);
	_uiComps.husband->SetState(-1); // TODO: Debugging purpose;

	_npcEmerged[2] = false;
	_uiComps.mother->ResetAnimation();
	_uiComps.mother->SetPosition(0, screenHeight);
	_uiComps.mother->SetState(-1); // TODO: Debugging purpose;

	_npcEmerged[3] = false;
	_uiComps.dancingTownspeople->ResetAnimation();
	_uiComps.dancingTownspeople->SetPosition(0, screenHeight);
	_uiComps.dancingTownspeople->SetState(-1); // TODO: Debugging purpose;

	_npcEmerged[4] = false;
	_uiComps.ancestors->ResetAnimation();
	_uiComps.ancestors->SetPosition(0, screenHeight);
	_uiComps.ancestors->SetState(-1); // TODO: Debugging purpose;

	_uiComps.comboBox->ResetAnimation();
	_uiComps.comboValue->ResetAnimation();

	// Reset Player State
	_player = _player->GetPlayer();
	_player->Reset();

	// Setup the Razanya index
	_currRazanyaIndex = GetGameDataHub().GetCurrentGeneration() % 3;

	// Player Sprite Bindings
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya" + 
			std::to_wstring(_currRazanyaIndex) +
			L"_down01"),
		L"down1"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya" + 
			std::to_wstring(_currRazanyaIndex) +
			L"_down02"),
		L"down2"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya" + 
			std::to_wstring(_currRazanyaIndex) +
			L"_Left01"),
		L"left1"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya" + 
			std::to_wstring(_currRazanyaIndex) +
			L"_Left02"),
		L"left2"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya" + 
			std::to_wstring(_currRazanyaIndex) +
			L"_Right01"),
		L"right1"
	);
	_player->BindImage(
		ResourceManager::Get().GetImage(L"Razanya" + 
			std::to_wstring(_currRazanyaIndex) +
			L"_Right02"),
		L"right2"
	);

	// Game Play Initialization
	_player->SetPosition(2, 4);
	_player->ChangeTag(L"down1");
	_player->SetHP(_player->GetMaxHP());
	_player->SetAttackDamage(PLAYER_DEFAULT_AD);
	_player->SetMaxOxygenLevel(PLAYER_DEFAULT_MAX_OXYGEN_LEVEL);
	_player->SetOxygenLevel(_player->GetMaxOxyLevel());
	_player->SetScore(0);
	_player->SetCombo(0);
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
		_reverseArrowKeys = true;
		_player->SetCombo(2);
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

	_playerOxySystem->ResetReduceOxy();
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
	_gloryOfFamilyScore = GetGameDataHub().GetMaxScore();
	_mothersScore = GetGameDataHub().GetPreviousUser().score;
	_uiComps.gloryOfFamily->SetText(__WStringifyGloryHall(_gloryOfFamilyScore).c_str());
	_uiComps.honorOfAncestor->SetText(__WStringifyMothersHonor(_mothersScore).c_str());
	_uiComps.currentHonor->SetText(__WStringifyCurrentHonor(_player->GetCurrScore()).c_str());

	_uiComps.additionalScore->SetText(L"0");	// DEBUG
	_uiComps.depth->SetText(L"0M");	// DEBUG

	// State Display
	_uiComps.currentState->SetState(
		static_cast<int>(PlayerStateAnimation::IDLE)
	);

	// Turn off Game End Components
	_gameEndSceneContainer->SetActive(false);
	_endComps.gotohistory->SetActive(false);
	_endComps.gameEndBG->SetActive(false);

	//Turn off history componets
	_historyComps.historyBG->SetActive(false);
	_historyComps.entryButton->SetActive(false);
	_historyContainer->SetActive(false);

	// Change Systems.
	__InitSystems();
	int length = (int)_historyComps.name->text.length();
	if (!_historyComps.name->text.empty())
	{
		for (int i = 0; i < length; ++i)
		{
			_historyComps.name->text.pop_back();
		}
	}
}


std::wstring PlayScene::__WStringifyEndingMessage1() {
	wchar_t buffer[50];
	swprintf_s(buffer, 
		L"-라자냐+ [-%d+]세,\n"
		L"무크티니 동굴 [-%d+]M에서 잠들다.", 
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
	wchar_t buffer[80];
	swprintf_s(buffer, 
		L"그녀의 활약은 [-%d+] 만큼 훌륭했으며,\n"
		L"그녀의 어머니를 능가했고,\n"
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

void PlayScene::__AutoValveCondition(std::function<bool()> condition) {
	static bool valve = true;
	if (valve) {	// valve is true 
		if (condition()) {	// true
			_nextLevelUpCeiling = _nextLevelUpCeiling + 50;
			_isLevelUpAnimationPlaying = true;	
			valve = false;	// Lock the valve
		}
	}
	else {
		valve = !condition();
	}
}


void PlayScene::LevelUpAnimationUpdate(double dt) {
	static int count = 0;
	static double elapsedTime = 0.0;

	if (!_isLevelUpAnimationPlaying) return;

	elapsedTime += dt;

	while (elapsedTime >= 0.2) {
		elapsedTime -= 0.2;

		if (count & 0b1) {
			_uiComps.levelUpSign->SetActive(false);
		} else {
			_uiComps.levelUpSign->SetActive(true);
		}

		if (count++ > 10) {
			count = 0;
			elapsedTime = 0.0;
			_isLevelUpAnimationPlaying = false;
		}
	}
}
