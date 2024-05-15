#pragma once
#include "CollectiveRenderable.h"
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
END = 8
};

// Brick ����ü ����
struct Brick
{
  int block_score = 0; // �긯�� ����
  int block_downAir = 0; // �긯�� �μ��� ������ ���� �Ǵ� ����
  int block_health = 0;
  
  Brick(BrickType type)
  {
    switch (type)
    {
    case BrickType::DEFAULT:
    block_score = 1;
    block_downAir = 4; 
    block_health = 10;
          break;
    case BrickType::STONE:
    block_score = 1;
    block_downAir = 4;
    block_health = 30;
          break;
    case BrickType::ROCK:
    block_score = 1;
    block_downAir = 4;
    block_health = 60;
          break;
    case BrickType::BOMB:
    break;
    case BrickType::GOLD:
    block_score = 10;
    block_health = 20;
          break;
    case BrickType::OXYGEN:
    block_score = 1;
    block_downAir = 0;
    block_health = 20;
          break;
    case BrickType::RASGULLA:
    block_score = 1;
    block_downAir = 4;
    block_health = 1;
          break;
    case BrickType::GULAB_JAMUN:
    block_score = 1;
    block_downAir = 10;
    block_health = 1;
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
class BrickGraphics : public CollectiveRenderable<T> {

#ifndef NDEBUG
	BrickGraphics() 
    : CollectiveRenderable<T>(0, 0, 1, 1) {
		SetBorder(255, 0, 0);
    SetFillColor(255, 255, 255);
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
