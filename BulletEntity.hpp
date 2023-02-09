#pragma once
#include "EnemyEntity.hpp"
#include "Utils.hpp"
#include <vector>
#include <list>

class EnemyEntity;

class BulletEntity : public WorldSpaceEntity
{
public:
	BulletEntity(float x, float y, SDL_Texture* tex, int sortOrder, float damage, float speed, 
		float travelTime, Vector2 size, Vector2 explosionSize, bool facingRight, std::vector<SDL_Texture*> rightAnimation, std::vector<SDL_Texture*> leftAnimation, int enemiesDamageable);
	float damage;
	float speed;
	Uint32 lastPosUpdate;
	Uint32 lastAnimUpdate;
	//the time when the bullet was instantiated measured in milliseconds since the game started
	Uint32 startTime;
	Vector2 velocity;
	float animatedFPS = 12;
	//how long in seconds the bullet can travel before being destroyed
	float travelTime;
	size_t currAnimIndex;
	//how many enemies can be damaged by the bullet before it is destroyed
	int enemiesDamageable;
	void update() override;
	void updatePosition();
	void updateCollision();
	void updateAnimation();
	std::vector<SDL_Texture*> destroyAnimation;
	bool destroy = false;
	Vector2 size;
	Vector2 explosionSize;
};