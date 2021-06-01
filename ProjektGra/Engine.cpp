#include "Engine.h"


Engine::Engine(RenderWindow* w) :
	window(w) {}

std::vector<GameObject*> Engine::objects{};
std::vector<PhysicalObject*> Engine::phy_objects{};

void Engine::update(float dt)
{
	// render i ruch

	window->clear(Color(129, 57, 42, 255));

	for (auto target : objects)
	{
		target->ExecuteMove(dt);
		window->draw(*target->sprite);
	}

	window->display();


	// fizyka


}
