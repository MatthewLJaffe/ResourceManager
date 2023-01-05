#pragma once
#include "Entity.hpp"
#include "Transformable.hpp"
#include "Vector2.hpp"
#include "Assets.hpp"

class ArrowEntity : public Transformable, public Entity
{
public:
	Vector2* from;
	Vector2* to;
	ArrowEntity(Vector2* from, Vector2* to, float scale, SDL_Texture* tex, int sortOrder);
	void render() override;
	void update() override;
	void updateTransformState() override;
	~ArrowEntity();
};