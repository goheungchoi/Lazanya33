#pragma once
#include "IRenderable.h"
#include "GridDeque.h"
#include "Brick.h"
#include "BlockGenerationSystem.h"

class Wall :public IRenderable
{
private:

	int _blockDownAir;
	int _blockDestroyAir;
	int _blockScore;

	GridDeque<BrickType>_brickTypes;
	GridDeque<int>_brickHPs;
public:
	
	void PopFrontBricks()
	{

	}
	void PushBackBricks()
	{

	}
	void DamageBrick()
	{

	}
	void GetBrickTraits()
	{

	}
  
};