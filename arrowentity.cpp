#include "ArrowEntity.hpp"

ArrowEntity::ArrowEntity(Vector2 from, Vector2 to, float scale, SDL_Texture* tex, int sortOrder)
{
	this->from = from;
	this->to = to;
	this->scale = scale;
	this->tex = tex;
	this->pos = Vector2(0, 0);
	this->sortOrder = sortOrder;
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	enabled = true;
}

void ArrowEntity::render()
{
	if (!enabled) return;
	RenderWindow::Instance().setScale(scale, scale);
	float scaleConst = 4 / scale;
	RenderWindow::Instance().drawLine(utils::roundFloat(from.x + 208 * scaleConst), utils::roundFloat(from.y + 90 * scaleConst),utils::roundFloat(to.x + 208 * scaleConst),utils::roundFloat(to.y + 90 * scaleConst));

	Vector2 dir = to - from;
	dir.normalize();
	Vector2 right(1, 0);
	angle = double(right.angleBetween(dir));
	if (angle < 0)
		angle += 360;
	if (angle < 22.5 || angle > 337.5)
		tex = Assets::Instance().img_ArrowRight;
	else if (angle > 22.5 && angle < 67.5)
		tex = Assets::Instance().img_ArrowBottomRight;
	else if (angle > 67.5 && angle < 112.5)
		tex = Assets::Instance().img_ArrowDown;
	else if (angle > 112.5 && angle < 157.5)
		tex = Assets::Instance().img_ArrowBottomLeft;
	else if (angle > 157.5 && angle < 202.5)
		tex = Assets::Instance().img_ArrowLeft;
	else if (angle > 202.5 && angle < 247.5)
		tex = Assets::Instance().img_ArrowTopLeft;
	else if (angle > 247.5 && angle < 292.5)
		tex = Assets::Instance().img_ArrowUp;
	else if (angle > 292.5 && angle < 337.5)
		tex = Assets::Instance().img_ArrowTopRight;
	SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	Vector2 arrowPos;
	arrowPos.x = to.x + 208 * scaleConst - currentFrame.w / 2;
	arrowPos.y = to.y + 90 * scaleConst - currentFrame.h / 2;
	arrowPos -= dir * currentFrame.w / 2;
	RenderWindow::Instance().render(tex, currentFrame, { int(arrowPos.x), int(arrowPos.y), int(currentFrame.w), int(currentFrame.h) }, 0);
	RenderWindow::Instance().setScale(1, 1);
}

void ArrowEntity::update()
{
	if (!enabled) return;
	updateTransformState();
}

void ArrowEntity::updateTransformState()
{
	transformState = GameTransformer::Instance().getTransformState();
	this->scale = 4.0f * transformState.scale.x;
}