#pragma once
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "Game.hpp"

class TurretEntity : public WorldSpaceEntity
{
public:
	TurretEntity(float x, float y, bool facingRight, float damage, float fireRate, float width, float height, std::vector<SDL_Texture*> turretFireImages, float health, bool cannon);
	float width;
	float height;
	void update() override;
	void takeDamage(float amount);

private:
	float fireRate;
	float damage;
	bool facingRight;
	bool cannon;
	std::vector<SDL_Texture*> turretFireAnim;
	std::vector<SDL_Texture*> turretDestroyAnimation;
	int bulletFireFrame;
	int currAnimIdx = 0;
	bool fired = false;
	bool firing = false;
	bool destroy = false;
	float animatedFPS = 12;
	float health;
	Uint32 lastUpdateTime;
	float currFireTime;
	float currAnimFrameTime;
	Vector2 bulletPosOffset;
	Vector2 missilePosOffset;
	void fireBullet(float dT);
	void playDestroyAnimation(float dT);
	void destroyTurret();
};