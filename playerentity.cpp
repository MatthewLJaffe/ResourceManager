#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float width, float height)
	: WorldSpaceEntity(x, y, scale, tex, sortOrder)
{
	currAnimState = Assets::Instance().imgs_PlayerWalkRight;
	velocity = Vector2(0, 0);
	this->width = width;
	this->height = height;
	bulletOffset = Vector2(15, 0);
	lastHandcannonUpdate = 0;
	lastHandcannonUpdate = 0;
	this->health = 100;
	this->maxHealth = 100;
	lastUpdate = Game::Instance().GetGameTime();
	std::string healthText = "Health: " + std::to_string(static_cast<int>(this->health));
	this->playerHealthDisplay = new TextEntity(8, 4, 4, healthText, 6, {0, 0, 0}, Assets::Instance().font_Body, 50, 20);
	Game::Instance().AddEntity(playerHealthDisplay, "MainGameState");
}

void PlayerEntity::update()
{
	if (!this->enabled) return;
	float curr = Game::Instance().GetGameTime();
	float dT = (curr - lastUpdate) / 1000.0f;
	if (currDamageTickCooldown > 0)
		currDamageTickCooldown -= dT;
	if (health > 0)
	{
		updatePosition(dT);
		updateCollision();
		updateGunFire(dT);
	}
	updateAnimation(dT);
	WorldSpaceEntity::update();
	timeSurvived += dT;
	lastUpdate = curr;
}

void PlayerEntity::updatePosition(float dT)
{

	if (InputManager::Instance().getADown())
	{
		facingRight = false;
		velocity.x = -walkSpeed;
	}
	else if (InputManager::Instance().getDDown())
	{
		facingRight = true;
		velocity.x = walkSpeed;
	}
	else
	{
		velocity.x = 0;
	}
	*pos += velocity * dT;
}

void PlayerEntity::updateCollision()
{
	if (pos->x > 1600)
		pos->x = 1600;
	if (pos->x < -1600)
		pos->x = -1600;
	std::vector<EnemyEntity*> enemies = Game::Instance().GetMainGameState()->enemies;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (utils::boxCollision(pos->x, pos->y, width, height, enemies[i]->pos->x, enemies[i]->pos->y, enemies[i]->width, enemies[i]->height))
		{
			takeDamage(enemies[i]->damage);
		}
	}
}

void PlayerEntity::render()
{
	WorldSpaceEntity::render();
}

void PlayerEntity::takeDamage(float amount)
{
	if (health < 0 || currDamageTickCooldown > 0) return;
	health -= amount;
	std::string displayText = "Health: " + std::to_string(static_cast<int>(health));
	currDamageTickCooldown = damageTickCooldown;
	if (health <= 0)
	{
		displayText = "Health: 0";
		std::cout << "die" << std::endl;
		currAnimIdx = 0;
		currAnimFrameTime = 0;
		if (facingRight)
			currAnimState = Assets::Instance().imgs_PlayerDieRight;
		else
			currAnimState = Assets::Instance().imgs_PlayerDieLeft;
	}
	playerHealthDisplay->updateText(displayText);
}

bool PlayerEntity::posInView(Vector2 pos)
{
	return abs(this->pos->x - pos.x) <= 160;
}

void PlayerEntity::updateAnimation(float dT)
{
	currAnimFrameTime += dT;
	if (currAnimFrameTime >= 1.0f / animatedFPS) {
		currAnimIdx++;
		currAnimFrameTime = 0;
	}
	//death animation
	if (health <= 0)
	{
		//animation end switch to end screen
		if (currAnimIdx >= currAnimState.size())
		{
			enabled = false;
			Game::Instance().GetMainGameState()->gameOver(timeSurvived);
			return;
		}
	}
	else if (abs(velocity.x) > .01f)
	{
		if (facingRight)
			currAnimState = Assets::Instance().imgs_PlayerWalkRight;
		else
			currAnimState = Assets::Instance().imgs_PlayerWalkLeft;
		currAnimIdx %= currAnimState.size();
	}
	else
	{
		currAnimFrameTime = 0;
		currAnimIdx = 0;
		if (facingRight)
			tex = Assets::Instance().img_PlayerRight;
		else
			tex = Assets::Instance().img_PlayerLeft;
		return;
	}
	tex = currAnimState[currAnimIdx];

}

void PlayerEntity::updateGunFire(float dT)
{
	lastHandgunUpdate += dT;
	float rate = baseHangunFireRate * (handgunsEquipped - 1) + startHandgunFireRate;
	float bulletsUnrounded = rate * lastHandgunUpdate;
	int bulletsToFire = floor(bulletsUnrounded);
	if (bulletsToFire > 0)
	{
		//remaining time maintained
		lastHandgunUpdate = (bulletsUnrounded - static_cast<float>(bulletsToFire)) / rate;
		for (int i = 0; i < bulletsToFire; i++)
		{
			Vector2 bulletPos = Vector2(0, this->pos->y + bulletOffset.y);
			SDL_Texture* bulletTex;
			if (facingRight)
			{
				bulletPos.x = this->pos->x + bulletOffset.x;
				bulletTex = Assets::Instance().imgs_bulletDestroyRight[0];
			}
			else
			{
				bulletPos.x = this->pos->x - bulletOffset.x;
				bulletTex = Assets::Instance().imgs_bulletDestroyLeft[0];
			}
			Game::Instance().AddEntity(new BulletEntity(bulletPos.x, bulletPos.y, bulletTex, 6, 5, 100, 1.5, Vector2(5,3 ), Vector2(0, 0), facingRight, Assets::Instance().imgs_bulletDestroyRight, Assets::Instance().imgs_bulletDestroyLeft, 1));
		}
	}
	lastHandcannonUpdate += dT;
	rate = baseHandCannonFireRate * handcannonsEquipped;
	float missilesUnrounded = rate * lastHandcannonUpdate;
	int missilesToFire = floor(missilesUnrounded);
	if (missilesToFire > 0)
	{
		//remaining time maintained
		lastHandcannonUpdate = (missilesUnrounded - static_cast<float>(missilesToFire)) / rate;
		for (int i = 0; i < missilesToFire; i++)
		{
			Vector2 bulletPos = Vector2(0, this->pos->y + bulletOffset.y);
			SDL_Texture* bulletTex;
			if (facingRight)
			{
				bulletPos.x = this->pos->x + bulletOffset.x;
				bulletTex = Assets::Instance().imgs_missileDestroyRight[0];
			}
			else
			{
				bulletPos.x = this->pos->x - bulletOffset.x;
				bulletTex = Assets::Instance().imgs_missileDestroyLeft[0];
			}
			Vector2 missileSize(7, 5);
			Vector2 explosionSize(16, 16);
			Game::Instance().AddEntity(new BulletEntity(bulletPos.x, bulletPos.y , bulletTex, 8, 10, 150, 1, missileSize, explosionSize, facingRight, Assets::Instance().imgs_missileDestroyRight, Assets::Instance().imgs_missileDestroyLeft, 5));
		}
	}
}

void PlayerEntity::spawnTurret()
{
	if (!enabled) return;
	std::vector<SDL_Texture*> turretImages = Assets::Instance().imgs_turretRight;
	Vector2 turretPosOffset(12, 1);
	if (!facingRight)
	{
		turretPosOffset.x *= -1;
		turretImages = Assets::Instance().imgs_turretLeft;
	}
	Vector2 turretPos = turretPosOffset + *this->pos;
	TurretEntity* turret = new TurretEntity(turretPos.x, turretPos.y, facingRight, 10, 1, 23, 19, turretImages, 20, false);
	Game::Instance().AddEntity(turret);
}

void PlayerEntity::spawnCannon()
{
	std::vector<SDL_Texture*> cannonImages = Assets::Instance().imgs_CannonRight;
	Vector2 cannonPosOffset(12, 1);
	if (!facingRight)
	{
		cannonPosOffset.x *= -1;
		cannonImages = Assets::Instance().imgs_CannonLeft;
	}
	Vector2 cannonPos = cannonPosOffset + *this->pos;
	TurretEntity* turret = new TurretEntity(cannonPos.x, cannonPos.y, facingRight, 10, 1, 23, 19, cannonImages, 40, true);
	Game::Instance().AddEntity(turret);
}

void PlayerEntity::spawnSpikes()
{
	Vector2 spikesPosOffset(12, -4);
	if (!facingRight)
	{
		spikesPosOffset.x *= -1;
	}
	Vector2 spikesPos = spikesPosOffset + *this->pos;
	SpikesEntity* spikes = new SpikesEntity(spikesPos.x, spikesPos.y, 32, 14, 8, 5, 20);
	Game::Instance().AddEntity(spikes);
}

void PlayerEntity::spawnBomb()
{
	Vector2 bombPosOffset(6, -18);
	if (!facingRight)
	{
		bombPosOffset.x *= -1;
	}
	Vector2 bombPos = bombPosOffset + *pos;
	BombEntity* bomb = new BombEntity(bombPos.x, bombPos.y, 96, 64, 10, 100);
	Game::Instance().AddEntity(bomb);
}

void PlayerEntity::incrementHandguns()
{
	if (handgunsEquipped == 0)
		lastHandgunUpdate = Game::Instance().GetGameTime();
	handgunsEquipped++;
}

void PlayerEntity::incrementHandcannons()
{
	if (handcannonsEquipped == 0)
		lastHandcannonUpdate = 0;
	handcannonsEquipped++;
}

int PlayerEntity::getHandguns()
{
	return handgunsEquipped;
}

int PlayerEntity::getHandcannons()
{
	return handcannonsEquipped;
}

void PlayerEntity::addHealth(float amount)
{
	health += amount;
	if (health > maxHealth)
		health = maxHealth;
	std::string displayText = "Health: " + std::to_string(static_cast<int>(health));
	playerHealthDisplay->updateText(displayText);
}