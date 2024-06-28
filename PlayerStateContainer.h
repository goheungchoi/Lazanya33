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
	IDLE_1,
	WARMING_1,
	BURNING_1,
	IDLE_2,
	WARMING_2,
	BURNING_2,
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
		player_idle->SetFrameDurations({ 0.05 });
		player_idle->SetX(x);
		player_idle->SetY(y);

		Bitmap* idle_img1 = ResourceManager::Get().GetImage(L"ui_idle_state_1");
		Animation* player_idle1 = new Animation(
			idle_img1, 0, 300, true
		);
		player_idle1->SliceSpriteSheet(
			540,
			580,
			0, 0, 0, 0
		);
		player_idle1->SetFrameDurations({ 0.05 });
		player_idle1->SetX(x);
		player_idle1->SetY(y);

		Bitmap* idle_img2 = ResourceManager::Get().GetImage(L"ui_idle_state_2");
		Animation* player_idle2 = new Animation(
			idle_img2, 0, 300, true
		);
		player_idle2->SliceSpriteSheet(
			540,
			580,
			0, 0, 0, 0
		);
		player_idle2->SetFrameDurations({ 0.05 });
		player_idle2->SetX(x);
		player_idle2->SetY(y);

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

		Bitmap* warming_img1 = ResourceManager::Get().GetImage(L"ui_warming_state_1");
		Animation* player_warming1 = new Animation(
			warming_img1, 0, 300, true
		);
		player_warming1->SliceSpriteSheet(
			540,
			580,
			0, 0, 0, 0
		);
		player_warming1->SetFrameDurations({ 0.1 });
		player_warming1->SetX(x);
		player_warming1->SetY(y);

		Bitmap* warming_img2 = ResourceManager::Get().GetImage(L"ui_warming_state_2");
		Animation* player_warming2 = new Animation(
			warming_img2, 0, 300, true
		);
		player_warming2->SliceSpriteSheet(
			540,
			580,
			0, 0, 0, 0
		);
		player_warming2->SetFrameDurations({ 0.1 });
		player_warming2->SetX(x);
		player_warming2->SetY(y);

		// BURNING
		Bitmap* burning_img = ResourceManager::Get().GetImage(L"ui_burning_state");
		Animation* player_burning = new Animation(
			burning_img, 0, 300, true
		);
		player_burning->SliceSpriteSheet(
			545,
			580, 
			0, 0, 0, 0
		);
		player_burning->SetFrameDurations({ 0.1 });
		player_burning->SetX(x);
		player_burning->SetY(y);

		Bitmap* burning_img1 = ResourceManager::Get().GetImage(L"ui_burning_state_1");
		Animation* player_burning1 = new Animation(
			burning_img1, 0, 300, true
		);
		player_burning1->SliceSpriteSheet(
			545,
			580,
			0, 0, 0, 0
		);
		player_burning1->SetFrameDurations({ 0.1 });
		player_burning1->SetX(x);
		player_burning1->SetY(y);

		Bitmap* burning_img2 = ResourceManager::Get().GetImage(L"ui_burning_state_2");
		Animation* player_burning2 = new Animation(
			burning_img2, 0, 300, true
		);
		player_burning2->SliceSpriteSheet(
			545,
			580,
			0, 0, 0, 0
		);
		player_burning2->SetFrameDurations({ 0.1 });
		player_burning2->SetX(x);
		player_burning2->SetY(y);
		
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
			static_cast<int>(PlayerStateAnimation::IDLE_1),
			player_idle1
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::WARMING_1),
			player_warming1
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::BURNING_1),
			player_burning1
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::IDLE_2),
			player_idle2
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::WARMING_2),
			player_warming2
		);
		AddAnimation(
			static_cast<int>(PlayerStateAnimation::BURNING_2),
			player_burning2
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


