#include <ComponentSystem\InputComponent.h>
#include <DebugTools\DebugMemory.h>
#include <Windows.h>

void InputComponent::Input::update()
{
	if(GetAsyncKeyState(keycode))
	{
		func();
	}
	else if(notPressed)
	{
		notPressed();
	}
}

InputComponent::InputComponent(EntityManager::Entity* e)
{
	name = "InputComponent";
	parent = e;
}

void InputComponent::addInput(int key, fastdelegate::FastDelegate0<> func, fastdelegate::FastDelegate0<> notpressedFunc)
{
	Input* input = new Input();
	input->func = func;
	input->notPressed = notpressedFunc;
	input->keycode = key;
	inputs.push_back(input);
}

void InputComponent::update()
{
	for(uint i=0; i<inputs.size(); i++)
	{
		inputs[i]->update();
	}
}

InputComponent::~InputComponent()
{
	for(uint i=0; i<inputs.size(); i)
	{
		delete inputs[i];
		inputs.erase(inputs.begin()+i);
	}
}
