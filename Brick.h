#pragma once

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
	END = 8
};

// Brick 구조체 정의
struct Brick
{
	int block_score = 0; // 브릭의 점수
	int block_downAir = 0; // 브릭을 부수면 

	// 생성자 정의
	

	Brick(BrickType type)
	{
		switch (type)
		{
		case BrickType::DEFAULT:
			block_score = 1;
			block_downAir = 4; 
			break;
		case BrickType::STONE:
			block_score = 1;
			block_downAir = 4;
			break;
		case BrickType::ROCK:
			block_score = 1;
			block_downAir = 4;
			break;
		case BrickType::BOMB:
			block_score = 0; 
			break;
		case BrickType::GOLD:
			block_score = 10;
			block_downAir = 4;
			break;
		case BrickType::OXYGEN:
			block_score = 1;
			block_downAir = 0;
			break;
		case BrickType::RASGULLA:	
			block_score = 1;
			block_downAir = 4;
			break;
		case BrickType::GULAB_JAMUN:
			block_score = 1;
			block_downAir = 10;
			break;
		}
	}
};

//brick : struct로 만들기. brick의 특징 스프래드시트보고 확인
//brick 생성자에 enum넘겨 받고 생성자로 각각의 객체 변수 값초기화
//ex) brick(BrickType tyep){switch(type)case BrickType::Defalut..