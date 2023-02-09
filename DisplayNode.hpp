#pragma once
#include "Entity.hpp"
#include <vector>
#include "ArrowEntity.hpp"
#include "Transformable.hpp"
#include "ResourceManager.hpp"

class DisplayNode;

/// <summary>
/// encapsulation of an arrow entity and the target resource it is pointing to
/// </summary>
struct OutgoingArrow
{
	OutgoingArrow(std::string target, ArrowEntity* arrow);
	std::string target;
	ArrowEntity* arrow;
};

class DisplayNode : public Entity, public Transformable
{
public:
	// the scale of the entity before any zooming in our out
	const float defaultScale = 2;
	//center of the display graph 
	Vector2 viewportCenter = Vector2(208, 90);
	Vector2 size = Vector2(47, 47);

	/// <summary>
	/// returns the position of the topleft corner of the display node
	/// </summary>
	Vector2 getScreenPos(Vector2 viewportPos);

	/// <summary>
	/// size of display node in pixels
	/// </summary>
	/// 
	Vector2 screenSpaceSize();

	/// <summary>
	/// 
	/// </summary>
	void renderTextAtVerticalOffset(SDL_Texture* textImg, float yOffset);

	/// <summary>
	/// sets text displaying the amount of the item currently obtained
	/// </summary>
	void setDisplayAmount(int newAmount);
	bool posInCraftButton(Vector2 pos);
	bool displayCraftButton = false;
	DisplayNode(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name, int displayAmount, size_t maxChars);
	std::map<std::string, ArrowEntity*> outgoingArrows;
	std::vector<Vector2> points;
	std::string name;
	bool selected = false;
	int maxChars;
	Vector2 getCenterPos();
	void updateTransformState() override;
	void update() override;
	void render() override;
	SDL_Rect craftButtonRect = { 11,28,26,11 };
private:
	int displayAmount = 0;
	std::string displayName;
	SDL_Texture* nameTextImg;
	SDL_Texture* amountTextImg;
	SDL_Texture* buttonImg;
	SDL_Texture* buttonDownImg;
	SDL_Texture* buttonState;
	SDL_Texture* craftTextImg;

};