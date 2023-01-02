#pragma once
#include "Entity.hpp"
#include <vector>
#include "ArrowEntity.hpp"

class DisplayNode;

struct OutgoingArrow
{
	OutgoingArrow(DisplayNode* target, Vector2* targetOffset, Vector2* originOffset, ArrowEntity* arrow);
	DisplayNode* target;
	Vector2* targetOffset;
	Vector2* originOffset;
	ArrowEntity* arrow;
};

class DisplayNode : public Entity
{
public:

	DisplayNode(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name);
	std::vector<OutgoingArrow*> outgoingArrows;
	std::vector<Vector2> points;
	std::string name;
	SDL_Texture* textImg;
	void update() override;
	void render() override;
};