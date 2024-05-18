#include "pch.h"
#include "PlayScene.h"
#include "GridMap.h"
#include "Player.h"
#include "Wall.h"
#include "Container.h"

#include "SingleRenderable.h"

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

PlayScene::PlayScene()
	: _gridMap{ new GridMap(
			GRID_MAP_POSITION_X,
			GRID_MAP_POSITION_Y,
			wallNumRows, wallNumCols, 120, 120) },
	_player{ new Player() },
	_walls{ new Wall() },
	_brickGenSystem{ new BrickGenSystem(_walls) },
	_playerOxySystem{ new PlayerOxygenSystem(_player,PLAYER_OXYGEN_REDUCE_INITAL_VALUE) },
	_playerBrickInteractionSystem{ new PlayerBricksInteractionSystem(_player,_walls,_playerOxySystem)}
{	
	
	//_player->UpdateSpritePivotPosition(H_DIRECTION::CENTER, V_DIRECTION::BOTTOM);
	
	_letterContainer = new Container(0, 0, screenWidth, screenHeight);

	_letterComponents.background = new SingleSpriteRenderable<LetterComponents>();
	_letterComponents.letter = new Container(160, 160, 800, 500);

	_letterComponents.diagrams = new Container(120, 400, 800, 300);
	_letterComponents.leftArrowDiagram = new Container(0, 0, 144, 175);
	_letterComponents.downArrowDiagram = new Container(0, 0, 205, 232);
	_letterComponents.rightArrowDiagram = new Container(0, 0, 142, 188);

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
	
	/*_renderSystem->RegisterRenderableObject(_ui);
	_renderSystem->RegisterRenderableObject(_gridMap);*/
	

	_player->ChangeTag(L"lazanya_02");
	//_player->ChangeTag(L"player");
	_player = new GoldSeeker(_player);
}

void PlayScene::Update(const double deltaTime)
{
	//if Didn't init, init one time
	if (!DidInit)
	{
		InitScene();
		DidInit = true;
	}

	_ui->Rotate(deltaTime*100);
	PlayerUpdate(deltaTime);
	

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

void PlayScene::InitScene()
{
/* Load Sprites */
	// Letter Scene Sprite Bindings
	_letterComponents.background->BindSprite(
		ResourceManager::Get().GetImage(L"letter_background")
	);
	_letterComponents.background->BindCachedSprite(
		ResourceManager::Get().GetCachedImage(L"letter_background")
	);
	_letterComponents.leftArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"left_arrow_diagram")
	);
	_letterComponents.downArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"down_arrow_diagram")
	);
	_letterComponents.rightArrowDiagram->SetImage(
		ResourceManager::Get().GetImage(L"right_arrow_diagram")
	);


	// Player Sprite Bindings
	Bitmap* bitmap = ResourceManager::Get().GetImage(L"lazanya_02");
	_player->BindImage(bitmap, L"lazanya_02");
	_renderSystem->CachingHelper(_player);

	// Bind Player and Wall to GridMap
	_gridMap->AddGridItem(_walls);
	_gridMap->AddGridItem(_player);

/* Build UI Hierarchy */
	// UI Settings
	// TODO: Need a script file seperate.
	_letterComponents.letter->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_letterComponents.letter->SetText(
		L"자랑스러운 라자브 가문의 장녀 라자냐 33세여,\n"
		L"폭탄산 무크티니로 가거라.\n\n"

		L"라자냐의 여전사로서 누구보다 폭탄산 무크티니를 깊게 파\n"
		L"라자브 가문의 전설이 되거라\n\n"

		L"학교를 안 가는걸 명예로 여겨온\n"
		L"라자브 가문의 여자답게 글을 모르겠지.\n"
		L"그림으로 설명하마.");
	_letterComponents.letter->SetFont(24, FontStyleBold);

	_letterComponents.diagrams->SetPositionLayout(PositionLayout::LAYOUT_FIXED);
	_letterComponents.diagrams->SetDisplay(Display::FLEX);
	_letterComponents.diagrams->SetFlexAlignItem(FlexAlignItem::FLEX_CENTER);
	_letterComponents.diagrams->SetFlexJustifyContent(FlexJustifyContent::SPACE_EVENLY);
	_letterComponents.diagrams->AddChildComponent(
		_letterComponents.leftArrowDiagram
	);
	_letterComponents.diagrams->AddChildComponent(
		_letterComponents.downArrowDiagram
	);
	_letterComponents.diagrams->AddChildComponent(
		_letterComponents.rightArrowDiagram
	);

	_letterContainer->AddChildComponent(_letterComponents.letter);
	_letterContainer->AddChildComponent(_letterComponents.diagrams);

	_renderSystem->RegisterRenderableObject(_letterComponents.background);
	_renderSystem->RegisterRenderableObject(_letterContainer);
	//_renderSystem->CacheDataInRegistry();

	// Game Play Initialization
	_player->SetPosition(2, 4);
	_brickGenSystem->BrickGenInit();
	//°¡Á··Â ¼±ÅÃ ÀÌÀü¿¡ ÇÊ¿äÇÑ RenderableObject µî·ÏÇÏ±â.
	//TestSound:
	Music::soundManager->PlayMusic(Music::eSoundList::TEST, Music::eSoundChannel::BGM);
}

void PlayScene::EndScene()
{

}

void PlayScene::PlayerUpdate(const double deltaTime)
{
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
		&& _walls->GetBrick(_player->GetPositionY(), _player->GetPositionX() - 1).type
		!= BrickType::NONE)
	{
		_playerBrickInteractionSystem->ApplyDamageToBrickByPlayer
		(_player->GetPositionY(), _player->GetPositionX() - 1,
			VK_LEFT, _countWallPop,deltaTime);
	}
	//if getkey Right and it's in the play screen and if brick type is not NONE, MoveRight
	if (Input::inputManager->IsTurnDn(VK_RIGHT)
		&& _player->GetPositionX() < 4
		&& _walls->GetBrick(_player->GetPositionY(), _player->GetPositionX() + 1).type
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
	Debug.Log(_playerOxySystem->GetAmountOfReduceOxy());
}
