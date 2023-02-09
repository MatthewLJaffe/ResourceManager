#pragma once
#include "Entity.hpp"
#include "Transformable.hpp"

/// <summary>
/// entity whose position represents a world space coordinate
/// </summary>
class WorldSpaceEntity : public Entity, public Transformable
{
public:
	WorldSpaceEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder);
	void render() override;
	void updateTransformState() override;
	void update() override;
	float originalScale;
	const Vector2 screenCenterOffset = Vector2(160, 153);

};