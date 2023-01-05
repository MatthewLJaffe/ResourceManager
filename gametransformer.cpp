#include "GameTransformer.hpp"

TransformState::TransformState()
{
	translation = Vector2(0, 0);
	rotation = 0;
	scale = Vector2(1, 1);
}

TransformState::TransformState(Vector2 pos, float rot, Vector2 scale)
	: translation(pos), rotation(rot), scale(scale)
{}

GameTransformer& GameTransformer::Instance()
{
	static GameTransformer gameTransformer;
	return gameTransformer;
}

void GameTransformer::resetGameTransformations()
{
	while (!transformStack.empty())
		transformStack.pop();
	gameTranslation.x = 0;
	gameTranslation.y = 0;
	gameScale.x = 1;
	gameScale.y = 1;
	gameRotation = 0;
}

TransformState GameTransformer::getTransformState()
{
	if (transformStack.empty())
	{
		return
		{
			gameTranslation,
			gameRotation,
			gameScale
		};
	}
	return 
	{ 
		transformStack.top().translation + gameTranslation, 
		transformStack.top().rotation + gameRotation, 
		transformStack.top().scale * gameScale 
	};
}

void GameTransformer::pushTransformState()
{
	transformStack.push(getTransformState());
	gameTranslation.x = 0;
	gameTranslation.y = 0;
	gameScale.x = 0;
	gameScale.y = 0;
	gameRotation = 0;
}

void GameTransformer::popTransformState()
{
	if (!transformStack.empty())
	{
		TransformState state = transformStack.top();
		transformStack.pop();
		gameTranslation = state.translation;
		gameScale = state.scale;
		gameRotation = state.rotation;
	}
	else
	{
		gameTranslation.x = 0;
		gameTranslation.y = 0;
		gameScale.x = 0;
		gameScale.y = 0;
		gameRotation = 0;
	}
}

void GameTransformer::translate(Vector2 translation)
{
	gameTranslation += translation;
}

void GameTransformer::rotate(float rotation)
{
	gameRotation += rotation;
}

void GameTransformer::setScale(Vector2 scale)
{
	gameScale = scale;
}

GameTransformer::GameTransformer() 
{
	gameRotation = 0;
	gameTranslation = Vector2(0, 0);
	gameScale = Vector2(1, 1);
}