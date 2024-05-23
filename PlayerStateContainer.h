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
		Bitmap* idle_img = ResourceManager::Get().GetImage(L"ui_idle_state");
		Animation* player_idle = new Animation(
			idle_img, 0, 300, true
		);
		player_idle->SliceSpriteSheet(
			540,
			580, 
			0, 0, 0, 0
		);
		player_idle->SetFrameDurations({ 0.2 });
		player_idle->SetX(x);
		player_idle->SetY(y);

		// WARMING
		Bitmap* warming_img = ResourceManager::Get().GetImage(L"ui_warming_state");
		Animation* player_warming = new Animation(
			warming_img, 0, 300, true
		);
		player_warming->SliceSpriteSheet(
			540,
			580, 
			0, 0, 0, 0
		);
		player_warming->SetFrameDurations({ 0.1 });
		player_warming->SetX(x);
		player_warming->SetY(y);

		// BURNING
		Bitmap* burning_img = ResourceManager::Get().GetImage(L"ui_burning_state");
		Animation* player_burning = new Animation(
			burning_img, 0, 300, true
		);
		player_burning->SliceSpriteSheet(
			540,
			580, 
			0, 0, 0, 0
		);
		player_burning->SetFrameDurations({ 0.1 });
		player_burning->SetX(x);
		player_burning->SetY(y);
		
		// DEAD
		Bitmap* dead_img = ResourceManager::Get().GetImage(L"ui_dead_state");
		Animation* player_dead = new Animation(
			dead_img, 0, 300, true
		);
		player_dead->SliceSpriteSheet(
			dead_img->GetWidth(),
			dead_img->GetHeight(), 
			0, 0, 0, 0
		);
		player_dead->SetX(x-60);
		player_dead->SetY(y+80);

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


