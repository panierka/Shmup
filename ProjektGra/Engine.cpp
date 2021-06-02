#include "Engine.h"


Engine::Engine(RenderWindow* w) :
	window(w) {}

std::vector<GameObject*> Engine::objects{};
std::vector<PhysicalObject*> Engine::phy_objects{};

void Engine::update(float dt)
{
	window->clear(Color(129, 57, 42, 255));

	for (auto target : objects)
	{
		target->ExecuteMove(dt);
	}

	for (int i = 0; i < phy_objects.size(); i++)
	{
		for (int j = 0; j < phy_objects.size(); j++)
		{
			if (i != j)
			{
				phy_objects[i]->collide(phy_objects[j]);
			}
		}
	}

	for (auto target : objects)
	{
		window->draw(*target->sprite);
	}

	window->display();
}
