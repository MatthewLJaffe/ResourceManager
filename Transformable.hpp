#pragma once
#pragma once
#include "GameTransformer.hpp"
class Transformable
{
public:
	Transformable();
	TransformState transformState;
	TransformState lastTransfromState;
	virtual void updateTransformState();
};