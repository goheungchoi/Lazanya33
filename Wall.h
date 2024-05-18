#pragma once
#include "GridItem.h"
#include "GridDeque.h"
#include "Brick.h"

constexpr std::size_t WALL_NUM_ROWS = 14;
constexpr std::size_t WALL_NUM_COLS = 5;

class Wall :public GridItem
{
private:
	GridDeque<Brick> _bricks;
	//GridDeque<Gdiplus::CachedBitmap*> _brickSprites;
	GridDeque<CachedBitmap*> _brickSprites;

public:
	Wall() :
		_bricks(WALL_NUM_ROWS, WALL_NUM_COLS),
		_brickSprites(WALL_NUM_ROWS, WALL_NUM_COLS) {}
		///_brickSprites(WALL_NUM_ROWS, WALL_NUM_COLS){}
	~Wall(){}	


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

	void DestroyBrick(int row, int col) {
		// 벽돌 부수면 렌더링만 안해버림.
		//_brickSprites.At(row, col) = nullptr;
		_bricks.At(row, col).type = BrickType::NONE;
		_brickSprites.At(row, col) = nullptr;
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

		// Reset the global transformation.
		g.SetTransform(&t);
	}
  
};