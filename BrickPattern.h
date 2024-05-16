#pragma once
#include "Brick.h"

constexpr std::size_t patternNRows = 3;
constexpr std::size_t patternNCols = 5;

struct BrickPattern
{

	BrickType patterns[15]
	{
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT
	};

	BrickType lvl1_Pattern1[15]
	{
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::STONE
	};
	BrickType lvl1_Pattern2[15]
	{
		BrickType::DEFAULT,BrickType::ROCK,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::GOLD,
		BrickType::STONE,BrickType::DEFAULT,BrickType::ROCK,BrickType::STONE,BrickType::BOMB
	};	
	BrickType lvl1_Pattern3[15]
	{
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::BOMB,
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::GOLD
	};	
	BrickType lvl1_Pattern4[15]
	{
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::BOMB,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT
	};	
	BrickType lvl1_Pattern5[15]
	{
		BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,
		BrickType::STONE,BrickType::STONE,BrickType::BOMB,BrickType::DEFAULT,BrickType::STONE
	};	
	BrickType lvl1_Pattern6[15]
	{
		BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::BOMB,BrickType::STONE,BrickType::DEFAULT,
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::OXYGEN,BrickType::DEFAULT
	};	
	BrickType lvl1_Pattern7[15]
	{
		BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,
		BrickType::BOMB,BrickType::BOMB,BrickType::GOLD,BrickType::BOMB,BrickType::BOMB,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT
	};	
	BrickType lvl1_Pattern8[15]
	{
		BrickType::STONE,BrickType::STONE,BrickType::OXYGEN,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::DEFAULT,BrickType::GOLD,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,
		BrickType::STONE,BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT
	};	
	BrickType lvl1_Pattern9[15]
	{
		BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::OXYGEN,BrickType::DEFAULT,
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::OXYGEN
	};	
	BrickType lvl1_Pattern10[15]
	{
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::DEFAULT,
		BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,BrickType::DEFAULT,BrickType::STONE,
		BrickType::DEFAULT,BrickType::DEFAULT,BrickType::DEFAULT,BrickType::STONE,BrickType::OXYGEN
	};

	struct SubscriptHelper {
		BrickType* patternsRow;

		BrickType& operator[](std::size_t col) {
			return patternsRow[col];
		}
	};

	SubscriptHelper operator[](std::size_t row) {
		return SubscriptHelper{ patterns + row * patternNCols };
	}
};
