#include "Engine.h"

Shader Engine::shader{};

Engine::Engine(RenderWindow* w) :
	window(w) 
{
	shader.loadFromFile("../Assets/effect_shader.frag", Shader::Fragment);
	shader.setUniform("flashColor", Glsl::Vec4(1, 1, 1, 1));
}

std::vector<std::unique_ptr<PhysicalObject>> Engine::objects{};

void Engine::update(float dt)
{
	window->clear(Color(73, 84, 123, 255));

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->execute_move(dt);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			if (objects.size() <= i || objects.size() <= j)
			{
				print("zly zakres");
				continue;
			}

			if (i != j)
			{
				objects[i]->collide(objects[j]);
			}
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->render(window);
	}

	//
	//for (auto target : phy_objects)
	//{

	//	RectangleShape r;
	//	r.setSize(Vector2f(target->collider->width, target->collider->height));
	//	r.setOrigin(Vector2f(target->collider->width, target->collider->height) / 2.f);
	//	r.setPosition(Vector2f(target->collider->left, target->collider->top));
	//	r.setFillColor(Color::Color(0, 255, 0, 100));

	//	window->draw(r);
	//}
	//

	window->display();
}
