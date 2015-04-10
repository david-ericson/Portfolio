#include "GameObject.h"

void GameObject::Draw(Core::Graphics& graphics)
{
	shape.Draw(graphics, position);
}