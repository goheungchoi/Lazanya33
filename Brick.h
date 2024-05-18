#pragma once

#include "SpritePack.h"
#include "ResourceManager.h"
//add
// BrickType 열거형 정의
enum class BrickType
{
DEFAULT,
STONE,
ROCK,
BOMB,
GOLD,
OXYGEN,
RASGULLA,
GULAB_JAMUN,
NONE,
END = 9
};

// Brick 구조체 정의
struct Brick
{
  int blockScore = 0; // 브릭의 점수
  double blockDownAir = 0; // 브릭을 부수면 공기의 감소 또는 증가
  int blockHealth = 0;		
	BrickType type;

	Brick() {
		blockScore = 0; 
    blockDownAir = 0; 
    blockHealth = 0;
		type = BrickType::NONE;
	}

  Brick(BrickType type)
  {
    switch (type)
    {
    case BrickType::DEFAULT:
    blockScore = 1;
    blockDownAir = 4; 
    blockHealth = 10;
		type = BrickType::DEFAULT;
    break;

    case BrickType::STONE:
    blockScore = 1;
    blockDownAir = 4;
    blockHealth = 30;
		type = BrickType::STONE;
		break;
			
    case BrickType::ROCK:
    blockScore = 1;
    blockDownAir = 4;
    blockHealth = 60;
		type = BrickType::ROCK;
    break;

    case BrickType::BOMB:
		type = BrickType::BOMB;
    break;

    case BrickType::GOLD:
    blockScore = 10;
    blockHealth = 20;
		type = BrickType::GOLD;
    break;

    case BrickType::OXYGEN:
    blockScore = 1;
    blockDownAir = 0;
    blockHealth = 20;
		type = BrickType::OXYGEN;
    break;

    case BrickType::RASGULLA:
    blockScore = 1;
    blockDownAir = 4;
    blockHealth = 1;
		type = BrickType::RASGULLA;
    break;

    case BrickType::GULAB_JAMUN:
    blockScore = 1;
    blockDownAir = 10;
    blockHealth = 1;
		type = BrickType::GULAB_JAMUN;
    break;
    }
  }
};

//brick : struct로 만들기. brick의 특징 스프래드시트보고 확인
//brick 생성자에 enum넘겨 받고 생성자로 각각의 객체 변수 값초기화
//ex) brick(BrickType tyep){switch(type)case BrickType::Defalut..

// Need to do something with these brick graphics things...
// The sprite register code is at Engine.cc line 55.
template<class T>
class BrickGraphics : public SpritePack<T> {};

class BDefault : public BrickGraphics<BDefault> {};

class BStone : public BrickGraphics<BStone> {};

class BRock : public BrickGraphics<BRock> {};

class BBomb : public BrickGraphics<BBomb> {};

class BGold : public BrickGraphics<BGold> {};

class BOxygen : public BrickGraphics<BOxygen> {};

inline Gdiplus::CachedBitmap* GetBrickSprite(BrickType brickType, const std::wstring& tag) {
	switch (brickType)
	{
	case BrickType::DEFAULT:
	{
		return BDefault::GetCachedSprite(tag);
	}
	case BrickType::STONE:
	{
		return BStone::GetCachedSprite(tag);
	}
	case BrickType::ROCK:
	{
		return BRock::GetCachedSprite(tag);
	}
	case BrickType::BOMB:
	{
		return BRock::GetCachedSprite(tag);
	}
	case BrickType::GOLD:
	{
		return BGold::GetCachedSprite(tag);
	}
	case BrickType::OXYGEN:
	{
		return BOxygen::GetCachedSprite(tag);
	}
	case BrickType::RASGULLA:
	{
		return BDefault::GetCachedSprite(tag);
	}
	case BrickType::GULAB_JAMUN:
	{
		return BDefault::GetCachedSprite(tag);
	}
	}
}
