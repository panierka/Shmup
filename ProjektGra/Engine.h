#pragma once
//#include<SFML/Graphics.hpp>
#include"Classes.h"

using namespace sf;

class Engine;
class GameObject;
class PhysicalObject;

class Engine
{
public:
	static std::vector<std::shared_ptr<GameObject>> objects;
	static std::vector<std::shared_ptr<PhysicalObject>> phy_objects;
	static Shader shader;
	
private:
	RenderWindow* window;

public:
	Engine(RenderWindow*);

	void update(float);
};

