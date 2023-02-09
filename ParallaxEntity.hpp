#pragma once
#include "Entity.hpp"
#include "Game.hpp"

class ParallaxEntity : public Entity
{
public:
	ParallaxEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float scrollSpeed);
	/// rate that the parralax scrolls relative to the displacment of the player
	float scrollSpeed;
	void update() override;
	void render() override;
	Vector2 leftPos;
	Vector2 rightPos;
	float maxX = 480;
	float minX = -480;
	float lastOffset;
};

