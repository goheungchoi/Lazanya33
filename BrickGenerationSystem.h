#pragma once
#include"BrickPattern.h"
#include"Wall.h"

// ��� ������Ʈ�� ��� ���� �̿��ؼ� ��� ����ؼ� ����
#define BRICKS 15

// TODO: �긯 ���� ��ȹ���� ������ 
// ���� h ���� ���� ���ϵ� ����
// �׸��� ���� H ���Ͽ��� ���� �о����
constexpr std::size_t TOTAL_NUM_PATTERNS = 1;

class BrickGenSystem
{
private:
	BrickPattern _patterns[TOTAL_NUM_PATTERNS];
	BrickPattern* _pNextPattern;
	Wall* _wall;
public:
	BrickGenSystem(Wall* wall) :_wall(wall) {}
	~BrickGenSystem(){}

	void ReadNextPattern() {
		// TODO: ������ ���� �������� ���� ���� �̾ƿ;ߵ�.
		_pNextPattern = &_patterns[0];
	}

	void GenerateNextRows()
	{
		BrickPattern& p = *_pNextPattern;
		for (std::size_t i = 0; i < patternNRows; ++i) {
			_wall->PushBackBricks({
				Brick(p[i][0]),
				Brick(p[i][1]),
				Brick(p[i][2]),
				Brick(p[i][3]),
				Brick(p[i][4])
			});
			/*_wall->PushBackBrickSprites({
				GetBrickSprite(p[i][0], L"01"),
				GetBrickSprite(p[i][1], L"01"),
				GetBrickSprite(p[i][2], L"01"),
				GetBrickSprite(p[i][3], L"01"),
				GetBrickSprite(p[i][4], L"01"),
			});*/

			_wall->PushBackBrickSprites({
				new BDefault(),
				new BDefault(),
				new BDefault(),
				new BDefault(),
				new BDefault()
			});
		}
	}
};