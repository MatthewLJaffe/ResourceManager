#include "ResourceEntity.hpp"

ResourceEntity::ResourceEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name, float width, float height, ResourceSpawner* resourceSpanwer)
	: WorldSpaceEntity(x, y, scale, tex, sortOrder)
{
	this->resourceName = name;
	this->width = width;
	this->height = height;
	this->resourceSpawner = resourceSpanwer;
}

void ResourceEntity::update()
{
	WorldSpaceEntity::update();
	detectCollision();
}

void ResourceEntity::detectCollision()
{
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	if (utils::boxCollision(pos->x, pos->y, width, height, player->pos->x, player->pos->y, player->width, player->height))
	{
		ResourceManager::Instance().addNode(resourceName);
		resourceSpawner->resourceConsumed();
		Game::Instance().RemoveAndDeleteEntity(this);
	}
}