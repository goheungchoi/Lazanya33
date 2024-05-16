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
