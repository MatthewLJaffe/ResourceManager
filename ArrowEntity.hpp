#pragma once
#include "Entity.hpp"
#include "Vector2.hpp"
#include "Assets.hpp"

class ArrowEntity : public Entity
{
public:
	Vector2* from;
	Vector2* to;
	ArrowEntity(Vector2* from, Vector2* to, float scale, SDL_Texture* tex, int sortOrder);
	void render() override;
	void update() override;
	~ArrowEntity();
};