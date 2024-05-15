#pragma once
#include"BrickPattern.h"
#include"Wall.h"

// 블락 컴포넌트랑 블락 패턴 이용해서 블락 계속해서 생성
#define BRICKS 15

// TODO: 브릭 패턴 기획한테 받으면 
// 따로 h 파일 만들어서 패턴들 빼자
// 그리고 따로 H 파일에서 패턴 읽어오고
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
		// TODO: 레벨에 따라 랜덤으로 다음 패턴 뽑아와야됨.
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