#pragma once

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
	int block_downAir = 0; // �긯�� �μ��� 

	// ������ ����
	

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

//brick : struct�� �����. brick�� Ư¡ ���������Ʈ���� Ȯ��
//brick �����ڿ� enum�Ѱ� �ް� �����ڷ� ������ ��ü ���� ���ʱ�ȭ
//ex) brick(BrickType tyep){switch(type)case BrickType::Defalut..