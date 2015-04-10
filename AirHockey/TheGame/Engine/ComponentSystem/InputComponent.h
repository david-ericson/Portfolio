#include <ComponentSystem\Component.h>
#include <FastDelegate.h>
#include <vector>
using std::vector;

#pragma once
class InputComponent : public Component
{
	struct Input
	{
		int keycode;
		fastdelegate::FastDelegate0<> func;
		fastdelegate::FastDelegate0<> notPressed;
		void update();
	};
public:
	vector<Input*> inputs;
	ENGINE_SHARED InputComponent(EntityManager::Entity* e);
	ENGINE_SHARED void addInput(int key, fastdelegate::FastDelegate0<> func, fastdelegate::FastDelegate0<> notpressedFunc = nullptr);
	void update();
	ENGINE_SHARED ~InputComponent();
};

