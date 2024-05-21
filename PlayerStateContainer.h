#pragma once

#include "Container.h"

#include "Animation.h"

#include "ResourceManager.h"
#include "RandomGenerator.h"

#include "DebugConsole.h"

using namespace Gdiplus;

enum class PlayerStateAnimation {
	IDLE,
	WARMING,
	BURNING,
	DEAD,
	LENGTH
};

constexpr std::size_t PLAYER_STATE_NUM = static_cast<std::size_t>(PlayerStateAnimation::LENGTH);

class PlayerStateContainer : public Container {

public:
	PlayerStateContainer(int x, int y, int w, int h)
	: Container(x, y, w, h) {
		// IDLE
		Bitmap* idle_img = ResourceManager::Get().GetImage(L"anaerobic");
		Animation* player_idle = new Animation(
			idle_img, 0, 300, true
		);
		player_idle->SliceSpriteSheet(
			idle_img->GetWidth(),
			idle_img->GetHeight(), 
			0, 0, 0, 0
		);

		// WARMING
		Bitmap* warming_img = ResourceManager::Get().GetImage(L"tenacious_dwarf");
		Animation* player_warming = new Animation(
			warming_img, 0, 300, true
		);
		player_warming->SliceSpriteSheet(
			warming_img->GetWidth(),
			warming_img->GetHeight(), 
			0, 0, 0, 0
		);

		// BURNING
		Bitmap* burning_img = ResourceManager::Get().GetImage(L"naughty");
		Animation* player_burning = new Animation(
			burning_img, 0, 300, true
		);
		player_burning->SliceSpriteSheet(
			burning_img->GetWidth(),
			burning_img->GetHeight(), 
			0, 0, 0, 0
		);
		
		// DEAD
		Bitmap* dead_img = ResourceManager::Get().GetImage(L"play_button");
		Animation* player_dead = new Animation(
			dead_img, 0, 300, true
		);
		player_dead->SliceSpriteSheet(
			dead_img->GetWidth(),
			dead_img->GetHeight(), 
			0, 0, 0, 0
		);

		// Register animations
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::IDLE), 
			player_idle
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::WARMING), 
			player_warming
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::BURNING), 
			player_burning
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::DEAD), 
			player_dead
		);
	}

	void Render(Graphics& g) override {
		Container::Render(g);

		/*auto* anim = _animationController->GetCurrentAnimation();
		g.TranslateTransform(_position.X, _position.Y);
		anim ? anim->Render(g) : []() {}();
		g.TranslateTransform(-_position.X, -_position.Y);*/
	}
};


