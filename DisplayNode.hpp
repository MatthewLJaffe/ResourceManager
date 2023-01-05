#pragma once
#include "Entity.hpp"
#include <vector>
#include "ArrowEntity.hpp"
#include "Transformable.hpp"
#include "ResourceManager.hpp"

class DisplayNode;

struct OutgoingArrow
{
	OutgoingArrow(std::string target, ArrowEntity* arrow);
	std::string target;
	Vector2* originOffset;
	ArrowEntity* arrow;
};

class DisplayNode : public Entity, public Transformable
{
public:
	bool active = true;
	const float defaultScale = 4;
	Vector2 viewportCenter = Vector2(208, 90);
	Vector2 size = Vector2(48, 48);
	Vector2 getScreenPos(Vector2 viewportPos);
	Vector2 screenSpaceSize();
	DisplayNode(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name);
	std::vector<OutgoingArrow*> outgoingArrows;
	std::vector<Vector2> points;
	std::string name;
	SDL_Texture* textImg;
	Vector2 getCenterPos();
	void updateTransformState() override;
	void update() override;
	void render() override;
};