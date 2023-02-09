#include "TurretEntity.hpp"

TurretEntity::TurretEntity(float x, float y, bool facingRight, float damage, float fireRate, float width, float height, std::vector<SDL_Texture*> turretFireImages, float health, bool cannon)
	: WorldSpaceEntity(x, y, 4, turretFireImages[0], 7)
{
	this->facingRight = facingRight;
	this->damage = damage;
	this->fireRate = fireRate;
	this->width = width;
	this->height = height;
	this->cannon = cannon;
	this->turretFireAnim = turretFireImages;
	this->health = health;
	this->currFireTime = 0;
	bulletPosOffset = Vector2(16, -5);
	missilePosOffset = Vector2(16, -5);
	if (!facingRight)
	{
		bulletPosOffset.x *= -1;
		missilePosOffset.x *= -1;
	}
	Game::Instance().GetMainGameState()->turrets.push_back(this);
	if (cannon)
	{
		if (facingRight)
			turretDestroyAnimation = Assets::Instance().imgs_MissileTurretDestroyRight;
		else
			turretDestroyAnimation = Assets::Instance().imgs_MissileTurretDestroyLeft;
	}
	else
	{
		if (facingRight)
			turretDestroyAnimation = Assets::Instance().imgs_TurretDestroyRight;
		else
			turretDestroyAnimation = Assets::Instance().imgs_TurretDestroyLeft;
	}
}

void TurretEntity::update()
{
	Uint32 current = Game::Instance().GetGameTime();
	float dT = (current - lastUpdateTime) / 1000.0f;
	if (health <= 0)
	{
		playDestroyAnimation(dT);
	}
	else
	{
		if (!firing)
		{
			currFireTime += dT;
			if (currFireTime > fireRate)
				firing = true;
		}
		else
		{
			fireBullet(dT);
		}
	}
	WorldSpaceEntity::update();
	lastUpdateTime = current;
	if (destroy)
		destroyTurret();
}

void TurretEntity::fireBullet(float dT)
{
	currAnimFrameTime += dT;
	if (currAnimFrameTime > dT / (1.0f / animatedFPS))
	{
		currAnimIdx++;
		currAnimFrameTime = 0;
		//shoot bullet on correct frame
		if (currAnimIdx >= bulletFireFrame && !fired)
		{
			fired = true;
			if (!cannon)
			{
				Vector2 bulletPos = pos + bulletPosOffset;
				SDL_Texture* bulletTex;
				if (facingRight)
				{
					bulletTex = Assets::Instance().imgs_bulletDestroyRight[0];
				}
				else
				{
					bulletTex = Assets::Instance().imgs_bulletDestroyLeft[0];
				}
				BulletEntity* bullet = new BulletEntity(bulletPos.x, bulletPos.y, bulletTex, 6, 10, 100, 1.5, Vector2(5, 3), Vector2(0, 0), facingRight, Assets::Instance().imgs_bulletDestroyRight, Assets::Instance().imgs_bulletDestroyLeft, 1);
				Game::Instance().AddEntity(bullet);
				//update so render is correct for this frame
				bullet->update();
			}
			else
			{
				Vector2 bulletPos = pos + missilePosOffset;
				SDL_Texture* missileTex;
				if (facingRight)
				{
					missileTex = Assets::Instance().imgs_missileDestroyRight[0];
				}
				else
				{
					missileTex = Assets::Instance().imgs_missileDestroyLeft[0];
				}
				Vector2 missileSize(7, 5);
				Vector2 explosionSize(16, 16);
				BulletEntity* missile = new BulletEntity(bulletPos.x, bulletPos.y, missileTex, 8, 10, 150, 1, missileSize, explosionSize, facingRight, Assets::Instance().imgs_missileDestroyRight, Assets::Instance().imgs_missileDestroyLeft, 8);
				Game::Instance().AddEntity(missile);
				//update so render is correct for this frame
				missile->update();
			}
		}
		if (currAnimIdx < turretFireAnim.size())
		{
			tex = turretFireAnim[currAnimIdx];
		}
		//animation over
		else
		{
			currAnimIdx = 0;
			fired = false;
			firing = false;
			currAnimFrameTime = 0;
			tex = turretFireAnim[0];
			currFireTime = 0;
		}
	}
}

void TurretEntity::takeDamage(float amount)
{
	if (this->health < 0) return;
	this->health -= amount;
	if (this->health < 0)
	{
		//reset animation varaibles for destroy animation
		currAnimFrameTime = 0;
		currAnimIdx = 0;
	}
}

void TurretEntity::playDestroyAnimation(float dT)
{
	currAnimFrameTime += dT;
	if (currAnimFrameTime > dT / (1.0f / animatedFPS))
	{
		currAnimFrameTime = 0;
		currAnimIdx++;
	}
	if (currAnimIdx < turretDestroyAnimation.size())
	{
		tex = turretDestroyAnimation[currAnimIdx];
	}
	//destroy turret
	else
	{
		destroy = true;
	}
}

void TurretEntity::destroyTurret()
{
	std::vector<TurretEntity*>& turrets = Game::Instance().GetMainGameState()->turrets;
	for (size_t i = 0; i < turrets.size(); i++)
	{
		if (turrets[i] == this)
		{
			turrets.erase(turrets.begin() + i);
			break;
		}
	}
	Game::Instance().RemoveAndDeleteEntity(this);
}