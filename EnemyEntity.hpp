#pragma once
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "Game.hpp"

class EnemyEntity : public WorldSpaceEntity
{
public:
	EnemyEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float health, float width, float height);
	void update() override;
	/// <summary>
	/// applies spike damage if damage cooldown is up
	/// </summary>
	/// <param name="amount">the amount of damage to take</param>
	/// <returns>true if spike damage was taken false otherwise</returns>
	bool takeSpikeDamage(float amount);
	void takeDamage(float amount);
	float width;
	float height;
	Uint32 lastAnimUpdate = 0;
	Uint32 lastUpdate = 0;
	float damage;

private:
	/// <summary>
	/// checks if any attackable entities are in range
	/// </summary>
	void checkForAttack();
	void updatePosition();
	void updateAnimation();
	void destroyEntity();
	void damageTurret();
	float animatedFPS = 12.0f;
	bool facingRight = true;
	bool destroy = false;
	float attackCooldown;
	float currAttackCooldown = 0;
	bool attacking = false;
	bool dealtDamage = false;
	const size_t attackDamageFrame = 6;
	vector<SDL_Texture*> currAnimState;
	float health;
	const float damageEffectTime = .2f;
	float currDamageEffectTime = .2f;
	//spike damage cooldown in seconds
	float spikeDamageCooldown = 1;
	//how long in seconds before spike damage can be taken
	float currSpikeDamageTime = 0;
	float walkSpeed = 25.0f;
	Vector2 velocity;
	size_t currAnimIdx = 0;
};