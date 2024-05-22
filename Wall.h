#pragma once
#include "GridItem.h"
#include "GridDeque.h"
#include "Brick.h"

#include "Animation.h"

constexpr std::size_t WALL_NUM_ROWS = 14;
constexpr std::size_t WALL_NUM_COLS = 5;

constexpr std::size_t NUM_BRICK_ANIMATIONS = 20;
constexpr std::size_t NUM_BOMB_ANIMATIONS = 10;

class Wall :public GridItem
{
private:
	GridDeque<Brick> _bricks;
	//GridDeque<Gdiplus::CachedBitmap*> _brickSprites;
	std::size_t brickDestructionAnimationIndex{ 0 };
	std::vector<Animation*> _brickDestructionAnimationPool;
	std::size_t bombExplosionAnimationIndex{ 0 };
	std::vector<Animation*> _bombExplosionAnimationPool;
	std::list<Animation*> _destroyAnimationList;
public:
	Wall() :
		_bricks(WALL_NUM_ROWS, WALL_NUM_COLS),
		_brickSprites(WALL_NUM_ROWS, WALL_NUM_COLS) {

		brickDestructionAnimationIndex = 0;
		_brickDestructionAnimationPool.resize(NUM_BRICK_ANIMATIONS);
		for (int i = 0; i < NUM_BRICK_ANIMATIONS; ++i) {
			Animation* brickAnim = new Animation(
			// Sprite Sheet
				ResourceManager::Get().GetImage(L"brick_destruction_effect"),
			// X, Y, loop
				0, 0, false
			);
			brickAnim->SliceSpriteSheet(145, 145, 0, 0, 0, 0);
			brickAnim->SetFrameDurations({ 0.05 });

			_brickDestructionAnimationPool[i] = brickAnim;
		}

		bombExplosionAnimationIndex = 0;
		_bombExplosionAnimationPool.resize(NUM_BOMB_ANIMATIONS);
		for (int i = 0; i < NUM_BOMB_ANIMATIONS; ++i) {
			Animation* bombAnim = new Animation(
			// Sprite Sheet
				ResourceManager::Get().GetImage(L"bomb_explosion_effect"),
			// X, Y, loop
				0, 0, false
			);
			bombAnim->SliceSpriteSheet(360, 360, 0, 0, 0, 0);
			bombAnim->SetFrameDurations({ 0.08 });
			_bombExplosionAnimationPool[i] = bombAnim;
		}
	}
		///_brickSprites(WALL_NUM_ROWS, WALL_NUM_COLS){}
	~Wall(){}	

	GridDeque<CachedBitmap*> _brickSprites;

	void PopFrontBricks()
	{
		_bricks.PopFront();
		_brickSprites.PopFront();
	}
	void PushBackBricks(std::initializer_list<Brick> ilist)
	{
		_bricks.PushBack(ilist);
	}

	/*void PushBackBrickSprites(std::initializer_list<Gdiplus::CachedBitmap*> ilist)
	{
		_brickSprites.PushBack(ilist);
	}*/

	void PushBackBrickSprites(std::initializer_list<CachedBitmap*> ilist)
	{
		_brickSprites.PushBack(ilist);
	}

	void DamageBrick(int row, int col, int dmg)
	{
		_bricks.At(row, col).blockHealth -= dmg;

		// TODO: Need to update sprites when the brick is in low HP.
		// _brickSprites.At(row, col) = GetBrickSprite(BrickType, tag);
	}

	BrickType GetBirckType(int row, int col)
	{
		return _bricks.At(row, col).type;
	}

	Brick& GetBrick(int row, int col)
	{
		return _bricks.At(row, col);
	}

	void DestroyBrick(int row, int col, bool isDown) {
		
		switch (_bricks.At(row, col).type)
		{
		case BrickType::BOMB: {
			std::size_t i = bombExplosionAnimationIndex++ % NUM_BOMB_ANIMATIONS;
			Animation* anim = _bombExplosionAnimationPool[i];
			Point screenPos{ col, row - isDown };
			_gridTransform.TransformPoints(&screenPos);
			anim->SetPosition(screenPos.X-120, screenPos.Y-120);
			anim->Trigger();
			_destroyAnimationList.push_back(anim);
		} break;
		default: {
			std::size_t i = brickDestructionAnimationIndex % NUM_BRICK_ANIMATIONS;
			Animation* anim = _brickDestructionAnimationPool[i];
			Point screenPos{ col, row - isDown };
			_gridTransform.TransformPoints(&screenPos);
			anim->SetPosition(screenPos.X, screenPos.Y);
			anim->Trigger();
			_destroyAnimationList.push_back(anim);
		}break;
		}
		
		// 벽돌 부수면 렌더링만 안해버림.
		//_brickSprites.At(row, col) = nullptr;
		_bricks.At(row, col).type = BrickType::NONE;
		_brickSprites.At(row, col) = nullptr;

		// Create Break animation and attach it.
	}

	void Update(double dt) {
		for (std::list<Animation*>::iterator it = _destroyAnimationList.begin(); 
			it != _destroyAnimationList.end();) {
			if (!(*it)->IsPlaying()) {
				it = _destroyAnimationList.erase(it);
			} else {
				(*it)->Update(dt);
				++it;
			}
    }
	}

	void Render(Graphics& g) override {
		// Grid items don't get applied global transformation.
		Matrix t;
		g.GetTransform(&t);
		g.ResetTransform();

		for (int i=1; i < 10; ++i) {
			for (int j=0; j < WALL_NUM_COLS; ++j) {
				Rect spriteRect;
				Point gridPos{ j, i };
				_gridTransform.TransformPoints(&gridPos);
				__SetSpriteRectPosition(gridPos, &spriteRect);

				Gdiplus::CachedBitmap* pBitmap = _brickSprites.At(i, j);
				pBitmap && g.DrawCachedBitmap(pBitmap, spriteRect.X, spriteRect.Y);
			}
		}

		for (auto* anim : _destroyAnimationList) {
			anim->Render(g);
		}

		// Reset the global transformation.
		g.SetTransform(&t);
	}
  
};