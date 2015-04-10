#include <LightManager.h>
#include <DebugTools\DebugMenus.h>
#include <vector>
using std::vector;

vector<Light*> lights;

void LightManager::initialize()
{
	//DebugMenus::addTab("Lighting");
}

int LightManager::addLight(glm::vec3 position,glm::vec3 color, float scalar)
{
	Light* light = new Light(position, color, scalar);
	lights.push_back(light);
	return lights[lights.size()-1]->index;
}

Light* LightManager::getLight(int index)
{
	/*int lightIndex = -1;
	for(unsigned int i=0; i<lights.size() && lightIndex == -1; i++)
	{
		lightIndex = (lights[i]->index == index)?i:lightIndex;
	}*/
	return lights[index];
}

int LightManager::getFirstLight()
{
	int index = -1;
	if(lights.size()>0)
	{
		index = lights[0]->index;
	}
	return index;
}

void LightManager::addDebugValueToLight(int index, menuType mt, char* tabName, float min, float max, int granuality)
{
	for(unsigned int i=0; i<lights.size(); i++)
	{
		if(lights[i]->index == index)
		{
			switch (mt)
			{
			case LightManager::pos:
				lights[i]->addDebugMenu(Light::pos, min, max, granuality, tabName); 
				DebugMenus::addRowToTab(tabName);
				break;
			case LightManager::diffColor:
				lights[i]->addDebugMenu(Light::diffColor, min, max, granuality, tabName); 
				DebugMenus::addRowToTab(tabName);
				break;
			case LightManager::visibility:
				lights[i]->addDebugMenu(Light::visibility, min, max, granuality, tabName); 
				break;
			case LightManager::scalar:
				lights[i]->addDebugMenu(Light::scalar, min, max, granuality, tabName); 
				break;
			}
		}
	}
}

void LightManager::update(float dt)
{
	for(unsigned int i=0; i<lights.size(); i++)
	{
		lights[i]->update(dt);
	}
}

void LightManager::shutdown()
{
	for(unsigned int i=0; i<lights.size(); i++)
	{
		delete lights[i];
		lights.erase(lights.begin()+i);
	}
}
