#include "Engine.h"
#include "DisplayHP.h"

Shader Engine::shader{};

Engine::Engine(RenderWindow* w) :
	window(w)
{
	shader.loadFromFile("../Assets/effect_shader.frag", Shader::Fragment);
	shader.setUniform("flashColor", Glsl::Vec4(1, 1, 1, 1));

	rectangle = make_unique<RectangleShape>(Vector2f(275.f, SCREEN_SIZE.y));
	rectangle->setFillColor(Color(0, 0, 0, 255));
	rectangle->setPosition(SCREEN_SIZE.x, 0);

	background = generate_sprite(TextureAtlas::texture_atlas["bck"], Vector2f(0, 0));

	line1 = generate_sprite(TextureAtlas::texture_atlas["line"], Vector2f(50, 0));

	line1->setPosition(230, 0);

	line2 = generate_sprite(TextureAtlas::texture_atlas["line"], Vector2f(50, 0));

	line2->setPosition(467, 0);

	for (int i = 0; i < 3; i++)
	{
		unique_ptr<Sprite> s = make_unique<Sprite>();
		s->setPosition(65 + i * 230, 400);
		s->setTexture(*TextureAtlas::texture_atlas["stats"]);
		stat_upgrades.push_back(std::move(s));
	}
}

std::vector<std::unique_ptr<PhysicalObject>> Engine::objects{};
std::vector<std::unique_ptr<Sprite>> Engine::stat_upgrades{};

Engine::~Engine()
{
	//delete window;
	delete background;
	delete line1;
	delete line2;
}

void Engine::set_stat_upgrades(const std::vector<Stat>& _data)
{
	for (int i = 0; i < stat_upgrades.size(); i++)
	{
		int _index = static_cast<int>(_data[i]);
		Vector2i v(_index % 3, _index / 3);
		Vector2i _frame(100, 150);
		stat_upgrades[i]->setTextureRect(IntRect(v * _frame, _frame));
	}
}

void Engine::update(float dt)
{
	window->clear(Color(73, 84, 123, 255));
	window->draw(*background);
	
	if (waves.intermission)
	{
		window->draw(*line1);
		window->draw(*line2);

		for (int i = 0; i < Engine::stat_upgrades.size(); i++)
		{
			window->draw(*Engine::stat_upgrades[i].get());
		}
	}

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

	window->draw(*rectangle);

	window->draw(*DisplayHP::health_text);
	window->draw(*DisplayHP::dodge_text);
	window->draw(*DisplayHP::ammo_text);
	window->draw(*DisplayHP::wave_text);

	//
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	RectangleShape r;
	//	r.setSize(Vector2f(objects[i]->collider->width, objects[i]->collider->height));
	//	//r.setOrigin(Vector2f(objects[i]->collider->width, objects[i]->collider->height) / 2.f);
	//	//r.setOrigin(Vector2f(50, 50));
	//	r.setPosition(Vector2f(objects[i]->collider->left, objects[i]->collider->top));
	//	r.setFillColor(Color::Color(0, 255, 0, 100));

	//	window->draw(r);
	//}
	//

	window->display();
}
