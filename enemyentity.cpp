#include "EnemyEntity.hpp"

EnemyEntity::EnemyEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float health, float width, float height)
	: WorldSpaceEntity(x, y, scale, tex, sortOrder)
{
	this->width = width;
	this->height = height;
	this->damage = 2;
	velocity = Vector2(0, 0);
	currAnimState = Assets::Instance().imgs_EnemyWalkRight;
	lastAnimUpdate = Game::Instance().GetGameTime();
	lastUpdate = Game::Instance().GetGameTime();
	this->health = health;
	Game::Instance().GetMainGameState()->enemies.push_back(this);
	spikeDamageCooldown = 1;
	currSpikeDamageTime = 0;
	this->attackCooldown = 1;
}

void EnemyEntity::update()
{
	float dT = (Game::Instance().GetGameTime() - lastUpdate) / 1000.0f;
	if (currDamageEffectTime > 0)
		currDamageEffectTime -= dT;
	if (currSpikeDamageTime > 0)
		currSpikeDamageTime -= dT;
	if (currAttackCooldown > 0)
		currAttackCooldown -= dT;
	if (health > 0)
	{
		updatePosition();
		checkForAttack();
	}
	updateAnimation();
	WorldSpaceEntity::update();
	lastUpdate = Game::Instance().GetGameTime();
	if (destroy)
		destroyEntity();
}

void EnemyEntity::updatePosition()
{
	if (attacking) return;
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	float dT = (Game::Instance().GetGameTime() - lastUpdate) / 1000.0f;
	if (player->pos.x - pos.x > this->width/2)
	{
		facingRight = true;
		velocity.x = walkSpeed;
	}
	else if (pos.x - player->pos.x > this->width/2)
	{
		facingRight = false;
		velocity.x = -walkSpeed;
	}
	else
	{
		this->attacking = true;
		currAnimIdx = 0;
		lastAnimUpdate = Game::Instance().GetGameTime();
		velocity.x = 0;
	}
	pos += velocity * dT;
}

void EnemyEntity::updateAnimation()
{
	Uint32 current = Game::Instance().GetGameTime();
	float dT = (current - lastAnimUpdate) / 1000.0f;
	int framesToUpdate = static_cast<int>(floor(dT / (1.0f / animatedFPS)));
	if (framesToUpdate > 0) {
		currAnimIdx += framesToUpdate;
		lastAnimUpdate = current;
	}
	//death animation
	if (health <= 0)
	{
		if (facingRight)
			currAnimState = Assets::Instance().imgs_AlienDieRight;
		else
			currAnimState = Assets::Instance().imgs_AlienDieLeft;
		//destroy entity
		if (currAnimIdx >= currAnimState.size())
		{
			destroy = true;
			return;
		}
		tex = currAnimState[currAnimIdx];
	}
	//attack animation
	else if (attacking)
	{
		if (facingRight)
			currAnimState = Assets::Instance().imgs_AlienAttackRight;
		else
			currAnimState = Assets::Instance().imgs_AlienAttackLeft;
		//in cooldown
		if (currAttackCooldown > 0)
		{
			currAnimIdx = 0;
			tex = currAnimState[0];
			return;
		}
		if (currAnimIdx >= attackDamageFrame && !dealtDamage)
		{
			dealtDamage = true;
			damageTurret();
		}
		if (currAnimIdx < currAnimState.size())
		{
			tex = currAnimState[currAnimIdx];
		}
		else
		{
			currAttackCooldown = attackCooldown;
			tex = currAnimState[0];
			dealtDamage = false;
			attacking = false;
		}
	}
	//walk animation
	else if (abs(velocity.x) > .01f)
	{
		currAnimIdx %= currAnimState.size();
		if (facingRight)
		{
			if (currDamageEffectTime > 0)
				currAnimState = Assets::Instance().imgs_AlienWalkRightDamage;
			else
				currAnimState = Assets::Instance().imgs_EnemyWalkRight;
		}
		else
		{
			if (currDamageEffectTime > 0)
				currAnimState = Assets::Instance().imgs_AlienWalkLeftDamage;
			else
				currAnimState = Assets::Instance().imgs_EnemyWalkLeft;
		}
		tex = currAnimState[currAnimIdx];
	}
	//idle
	else
	{
		currAnimIdx = 0;
		if (facingRight)
			tex = Assets::Instance().imgs_EnemyWalkRight[0];
		else
			tex = Assets::Instance().imgs_EnemyWalkLeft[0];
	}
}

void EnemyEntity::destroyEntity()
{
	vector<EnemyEntity*>& enemies = Game::Instance().GetMainGameState()->enemies;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] == this)
		{
			enemies.erase(enemies.begin() + i);
			Game::Instance().RemoveAndDeleteEntity(this);
		}
	}
}

void EnemyEntity::takeDamage(float amount)
{
	if (health <= 0) return;
	health -= amount;
	currDamageEffectTime = damageEffectTime;
	if (health <= 0)
	{
		lastAnimUpdate = Game::Instance().GetGameTime();
		velocity.x = 0;
		currAnimIdx = 0;
	}
}

bool EnemyEntity::takeSpikeDamage(float amount)
{
	if (currSpikeDamageTime > 0) return false;
	currSpikeDamageTime = spikeDamageCooldown;
	takeDamage(amount);
	return true;
}

void EnemyEntity::damageTurret()
{
	std::vector<TurretEntity*> turrets = Game::Instance().GetMainGameState()->turrets;
	for (size_t i = 0; i < turrets.size(); i++)
	{
		if (abs(turrets[i]->pos.x - pos.x) <= this->width / 2 + turrets[i]->width / 2)
		{
			turrets[i]->takeDamage(damage);
		}
	}
}

void EnemyEntity::checkForAttack()
{
	if (attacking) return;
	std::vector<TurretEntity*> turrets = Game::Instance().GetMainGameState()->turrets;
	for (size_t i = 0; i < turrets.size(); i++)
	{
		if (abs(turrets[i]->pos.x - pos.x) < this->width / 2 + turrets[i]->width / 2)
		{
			attacking = true;
			currAnimIdx = 0;
			lastAnimUpdate = Game::Instance().GetGameTime();
			
		}
	}
}

