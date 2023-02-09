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
	/// <summary>
	/// called every frame to reset all transformations applied
	/// </summary>
	void resetGameTransformations();
	/// <summary>
	/// called by all instances of Transformable to update their their translation rotation and scale
	/// </summary>
	/// <returns>the summation of all translations recorded on the transformation stack</returns>
	TransformState getTransformState();
	/// <summary>
	///  saves the current transformations on the transform stack
	/// </summary>
	void pushTransformState();
	/// <summary>
	/// resets transformations applied since the last call to pushTransformState() pops off the last transfrom state from the transform stack
	/// </summary>
	void popTransformState();
	/// <summary>
	/// applies a translation transformation that is recieved by all Transformable objects
	/// </summary>
	/// <param name="translation">translation applied</param>
	void translate(Vector2 translation);
	/// <summary>
	/// applies a rotation transformation that is recieved by all Transformable objects
	/// </summary>
	/// <param name="rotation">rotation applied</param>
	void rotate(float rotation);
	/// <summary>
	/// applies a scale transformation that is recieved by all Transformable objects
	/// </summary>
	/// <param name="scale">scale applied</param>
	void setScale(Vector2 scale);

private:
	GameTransformer();
	Vector2 gameTranslation;
	float gameRotation;
	Vector2 gameScale;
	std::stack<TransformState> transformStack;
};

