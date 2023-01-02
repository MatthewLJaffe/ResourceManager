#include "ArrowEntity.hpp"

ArrowEntity::ArrowEntity(Vector2* from, Vector2* to, float scale, SDL_Texture* tex, int sortOrder)
{
	this->from = from;
	this->to = to;
	this->scale = scale;
	this->tex = tex;
	this->sortOrder = sortOrder;
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	enabled = true;
}

void ArrowEntity::render()
{
	RenderWindow::Instance().setScale(scale, scale);
	RenderWindow::Instance().drawLine(from->x, from->y, to->x, to->y);

	Vector2 dir(to->x - from->x, to->y - from->y);
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
	RenderWindow::Instance().render(tex, currentFrame, { int(to->x - currentFrame.w/2), int(to->y - currentFrame.h/2), int(currentFrame.w), int(currentFrame.h) }, 0);
	RenderWindow::Instance().setScale(1, 1);
}

void ArrowEntity::update()
{

}

ArrowEntity::~ArrowEntity()
{
	delete from;
	delete to;
}
