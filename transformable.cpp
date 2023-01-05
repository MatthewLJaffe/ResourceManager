#include "Transformable.hpp"

Transformable::Transformable() {}

void Transformable::updateTransformState()
{
	lastTransfromState = transformState;
	transformState = GameTransformer::Instance().getTransformState();
}