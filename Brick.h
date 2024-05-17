#pragma once

#include "CollectiveRenderable.h"
#include "ResourceManager.h"
//add
// BrickType ������ ����
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

// Brick ����ü ����
struct Brick
{
  int blockScore = 0; // �긯�� ����
  double blockDownAir = 0; // �긯�� �μ��� ������ ���� �Ǵ� ����
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

//brick : struct�� �����. brick�� Ư¡ ���������Ʈ���� Ȯ��
//brick �����ڿ� enum�Ѱ� �ް� �����ڷ� ������ ��ü ���� ���ʱ�ȭ
//ex) brick(BrickType tyep){switch(type)case BrickType::Defalut..

// ��ģ������ ��������Ʈ �����͸� ������ �ְ�,
// �긯 ���ʷ��̼� �ý��ۿ����� �� ģ���� ��������Ʈ �����͵鸸 ������ ��.
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
