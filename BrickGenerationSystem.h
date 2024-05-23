#pragma once
//#include"BrickPattern.h"
#include"Wall.h"
#include "IPlayer.h"
#include "RandomGenerator.h"
// 블락 컴포넌트랑 블락 패턴 이용해서 블락 계속해서 생성
#define BRICKS 15

// TODO: 브릭 패턴 기획한테 받으면 
// 따로 h 파일 만들어서 패턴들 빼자
// 그리고 따로 H 파일에서 패턴 읽어오고
constexpr std::size_t TOTAL_NUM_PATTERNS = 1;

class BrickGenSystem
{
private:
	/*BrickPattern _patterns[TOTAL_NUM_PATTERNS];
	BrickPattern* _pNextPattern;*/
	Wall* _wall;
  IPlayer* _player;
public:
	BrickGenSystem(Wall* wall,IPlayer*player) : _wall(wall),_player(player) { 
		/*_patterns[0] ={
			BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
			BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
			BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT
		};
		_pNextPattern = &_patterns[0];*/
	}
	~BrickGenSystem(){}

	void SetIPlayer(IPlayer* player) {
		_player = player;
	}

	void BrickGenInit()
	{
		//pushBack none block
		for (int i = 0; i < 5; ++i)
		{
			_wall->PushBackBricks({
				BrickType::NONE,
				BrickType::NONE,
				BrickType::NONE,
				BrickType::NONE,
				BrickType::NONE
			});

			_wall->PushBackBrickSprites({
				nullptr, 
				nullptr, 
				nullptr,
				nullptr, 
				nullptr
			});
		}


		for (int i = 0; i < 3; ++i)
		{
			GenerateNextRows();
		}
	}

	//void ReadNextPattern() {
	//	// TODO: 레벨에 따라 랜덤으로 다음 패턴 뽑아와야됨.
	//	_pNextPattern = &_patterns[0];
	//}

	void GenerateNextRows()
	{
    std::string filename = ChangeTilePattern();
    std::vector<std::vector<std::string>> data= LoadPatternFromCSV(filename);
    
		for (std::size_t i = 0; i < 3; ++i)
		{
			_wall->PushBackBricks({
					Brick((BrickType)std::stoi(data[i][0])),
				Brick((BrickType)std::stoi(data[i][1])),
				Brick((BrickType)std::stoi(data[i][2])),
				Brick((BrickType)std::stoi(data[i][3])),
				Brick((BrickType)std::stoi(data[i][4]))
				});
			_wall->PushBackBrickSprites({
				GetBrickSprite((BrickType)std::stoi(data[i][0]),TypeToTag((BrickType)std::stoi(data[i][0]))),
				GetBrickSprite((BrickType)std::stoi(data[i][1]),TypeToTag((BrickType)std::stoi(data[i][1]))),
				GetBrickSprite((BrickType)std::stoi(data[i][2]),TypeToTag((BrickType)std::stoi(data[i][2]))),
				GetBrickSprite((BrickType)std::stoi(data[i][3]),TypeToTag((BrickType)std::stoi(data[i][3]))),
				GetBrickSprite((BrickType)std::stoi(data[i][4]),TypeToTag((BrickType)std::stoi(data[i][4]))),
			});
     
		}

	}
  std::vector<std::vector<std::string>> LoadPatternFromCSV(
    const std::string& fileName) {
 
    std::ifstream file(fileName);
    if (!file.is_open()) {
      throw std::runtime_error("Error! File not found: " + fileName);
      return {};
    }

    std::vector<std::vector<std::string>> data;
    std::string line;
    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string item;
      std::vector<std::string> parsedRow;

      while (std::getline(ss, item, ',')) {
        parsedRow.push_back(item);
      }
      data.push_back(parsedRow);
    }
    file.close();
    return data;
  }

  std::string ChangeTilePattern() {
    int blockLevel;
    int meter = _player->GetDownMeter();
    int tileLayer;
    int numberOfLayers;
    std::string nameOfCSV;
    
    int score = _player->GetCurrScore();
    // 스코어 60이하 일때
    if (meter <= 30) {
      int randomValue = RandomGenerator::Get(1,100);

      // 1에서 100 사이의 숫자를 생성하여 확률 결정
      if (randomValue <= 70) {
        blockLevel = 1;  
      }
      else {
        blockLevel = 2;  
      }
    } else if (meter <= 50) {
      {
        int randomValue = RandomGenerator::Get(1, 100);

        if (randomValue <= 50) {
          blockLevel = 1;
        }
        else
          blockLevel = 2;
      }
    } else if (meter <= 70) {
      {
        int randomValue = RandomGenerator::Get(1, 100);

        if (randomValue <= 40) {
          blockLevel = 1;
        }
        else if (randomValue <= 50) {
          blockLevel = 2;
        }
        else
          blockLevel = 3;
      }
    } else if (meter <= 85) {
      int randomValue = RandomGenerator::Get(1,100);

      if (randomValue <= 30) {
        blockLevel = 1;
      }
      else if (randomValue <= 40) {
        blockLevel = 2;
      }
      else
        blockLevel = 3;
    } else if (meter <= 100) {
      int randomValue = RandomGenerator::Get(1,100);

      if (randomValue <= 20) {
        blockLevel = 1;
      }
      else if (randomValue <= 50) {
        blockLevel = 2;
      }
      if (randomValue <= 80) {
        blockLevel = 3;
      }
      else {
        blockLevel = 4;
      }
    } else if (meter <= 125) {
      int randomValue = RandomGenerator::Get(1,100);

      if (randomValue <= 10) {
        blockLevel = 1;
      }
      else if (randomValue <= 30) {
        blockLevel = 2;
      }
      else if (randomValue <= 60) {
        blockLevel = 3;
      }
      else if (randomValue <= 90) {
        blockLevel = 4;
      }
      else {
        blockLevel = 5;
      }
    }
    else {
      int randomValue = RandomGenerator::Get(1,100);

      if (randomValue <= 10) {
        blockLevel = 2;
      }
      else if (randomValue <= 50) {
        blockLevel = 3;
      }
      else if (randomValue <= 80) {
        blockLevel = 4;
      }
      else
        blockLevel = 5;
    }

    switch (blockLevel) {
    case 1:
      numberOfLayers = 18;
      break;
    case 2:
      numberOfLayers = 18;
      break;
    case 3:
      numberOfLayers = 16;
      break;
    case 4:
      numberOfLayers = 13;
      break;
    case 5:
      numberOfLayers = 13;
      break;
    }
    tileLayer = RandomGenerator::Get(1, numberOfLayers);   

    nameOfCSV = "Block_Lv//Lv" + std::to_string(blockLevel) +
      +"//block_Lv"+std::to_string(blockLevel)+ "_Tile Layer " + std::to_string(tileLayer) + ".csv";
    return nameOfCSV;
  }

  std::wstring TypeToTag(BrickType type)
  {
    switch(type)
    {
    case BrickType::DEFAULT:
      return L"default";
    case BrickType::STONE:
      return L"stone";
    case BrickType::ROCK:
      return L"rock";
    case BrickType::BOMB:
      return L"bombR";
    case BrickType::GOLD:
      return L"gold";
    case BrickType::OXYGEN:
      return L"air";
    case BrickType::RASGULLA:
      return L"rasgulla";
    case BrickType::GULAB_JAMUN:
      return L"gulabjamun";
    }
  }
};