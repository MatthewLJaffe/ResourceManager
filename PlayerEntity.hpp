#pragma once
#include "BulletEntity.hpp"
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "InputManager.hpp"
#include <cmath>
#include <vector>
#include "Game.hpp"
#include "TurretEntity.hpp"
#include "SpikesEntity.hpp"
#include "BombEntity.hpp"

class PlayerEntity : public WorldSpaceEntity
{
public:
	PlayerEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float width, float height);
	bool facingRight = true;
	float width;
	float height;
	void update() override;
	bool posInView(Vector2 pos);
	void spawnTurret();
	void spawnBomb();
	void spawnSpikes();
	void spawnCannon();
	void incrementHandguns();
	void incrementHandcannons();
	int getHandguns();
	int getHandcannons();
	void addHealth(float amount);
private:
	Uint32 lastUpdate;
	int handgunsEquipped = 1;
	int handcannonsEquipped = 0;
	std::vector<SDL_Texture*> currAnimState;
	TextEntity* playerHealthDisplay;
	float lastHandcannonUpdate = 0;
	float lastHandgunUpdate = 0;
	const float baseHangunFireRate = .25;
	const float baseHandCannonFireRate = .25;
	const float startHandgunFireRate = .4f;
	float animatedFPS = 12.0f;
	float health;
	float maxHealth;
	const float damageTickCooldown = .1f;
	float currDamageTickCooldown = 0;
	float currAnimFrameTime = 0;
	Vector2 bulletOffset;
	Vector2 velocity;
	float walkSpeed = 60.0f;
	size_t currAnimIdx = 0;
	float timeSurvived = 0;
	void render() override;
	void updateGunFire(float dT);
	void updatePosition(float dT);
	void updateCollision();
	void updateAnimation(float dT);
	void takeDamage(float damage);

};
