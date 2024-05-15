#pragma once
#include "IRenderable.h"
#include "GridDeque.h"
#include "Brick.h"

constexpr std::size_t wallNumRows = 15;
constexpr std::size_t wallNumCols = 5;

class Wall :public IRenderable
{
private:
	GridDeque<Brick> _bricks;
	GridDeque<Gdiplus::CachedBitmap*> _brickSprites;

public:
	Wall() : 
	_bricks(wallNumRows,wallNumCols), 
		_brickSprites(wallNumRows, wallNumCols){}
	~Wall(){}	


	void PopFrontBricks()
	{
		_bricks.PopFront();
	}
	void PushBackBricks(std::initializer_list<Brick> ilist)
	{
		_bricks.PushBack(ilist);
	}

	void PushBackBrickSprites(std::initializer_list<Gdiplus::CachedBitmap*> ilist)
	{
		_brickSprites.PushBack(ilist);
	}

	void DamageBrick(int row, int col, int dmg)
	{
		_bricks.At(row, col).block_health -= dmg;
		// 브릭 현재 HP에 따라 스프라이트를 바꿔줌
		// _brickSprites.At(row, col) = GetBrickSprite(BrickType, tag);
	}

	Brick GetBrick(int row, int col)
	{
		return _bricks.At(row, col);
	}

	void DestroyBrick(int row, int col) {
		// 벽돌 부수면 렌더링만 안해버림.
		_brickSprites.At(row, col) = nullptr;
	}

	void Render(Graphics& g) override {
		for (int i=1; i < 10; ++i) {
			for (int j=0; j < wallNumCols; ++j) {
				Gdiplus::CachedBitmap* pBitmap = _brickSprites.At(i, j);
				pBitmap && g.DrawCachedBitmap(pBitmap, i, j);
			}
		}
	}
  
};