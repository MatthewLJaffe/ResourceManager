#pragma once
#include <stack>
#include "Vector2.hpp"

struct TransformState
{
	TransformState();
	TransformState(Vector2 translation, float rotation, Vector2 scale);
	Vector2 translation;
	float rotation;
	Vector2 scale;
};

class GameTransformer
{
public:
	static GameTransformer& Instance();
	GameTransformer(GameTransformer&) = delete;
	void resetGameTransformations();
	TransformState getTransformState();
	void pushTransformState();
	void popTransformState();
	void translate(Vector2 translation);
	void rotate(float rotation);
	void setScale(Vector2 scale);

private:
	GameTransformer();
	Vector2 gameTranslation;
	float gameRotation;
	Vector2 gameScale;
	std::stack<TransformState> transformStack;
};

