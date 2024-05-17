#pragma once

#include "CollectiveRenderable.h"
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

// 이친구들은 스프라이트 데이터만 가지고 있고,
// 브릭 제너레이션 시스템에서는 이 친구들 스프라이트 포인터들만 가지고 옴.
template<class T>
class BrickGraphics : public MultiSpriteRenderable<T> {

public:
#ifndef NDEBUG
	BrickGraphics() 
    : MultiSpriteRenderable<T>(0, 0, 1, 1) {
    MultiSpriteRenderable<T>::SetBorder(255, 0, 0);
	}
#endif

};

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
			auto it = BDefault::_pSpriteCacheData.find(tag);
			if (it == BDefault::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::STONE:
		{
			auto it = BStone::_pSpriteCacheData.find(tag);
			if (it == BStone::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::ROCK:
		{
			auto it = BRock::_pSpriteCacheData.find(tag);
			if (it == BRock::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::BOMB:
		{
			auto it = BBomb::_pSpriteCacheData.find(tag);
			if (it == BBomb::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::GOLD:
		{
			auto it = BGold::_pSpriteCacheData.find(tag);
			if (it == BGold::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::OXYGEN:
		{
			auto it = BOxygen::_pSpriteCacheData.find(tag);
			if (it == BOxygen::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::RASGULLA:
		{
			auto it = BDefault::_pSpriteCacheData.find(tag);
			if (it == BDefault::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	case BrickType::GULAB_JAMUN:
		{
			auto it = BDefault::_pSpriteCacheData.find(tag);
			if (it == BDefault::_pSpriteCacheData.end()) return nullptr;
			return it->second;
		}
	}
}
