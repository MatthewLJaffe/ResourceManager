#pragma once
#include "WorldSpaceEntity.hpp"
#include "Game.hpp"
#include "Utils.hpp"
#include "ResourceManager.hpp"
#include "ResourceSpawner.hpp"

class ResourceSpawner;

class ResourceEntity : public WorldSpaceEntity
{
public:
	ResourceEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name, float width, float height, ResourceSpawner* spawner);
	void update() override;
private:
	float width;
	float height;
	std::string resourceName;
	void detectCollision();
	ResourceSpawner* resourceSpawner;
};