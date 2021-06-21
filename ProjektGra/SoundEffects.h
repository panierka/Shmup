#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <list>
using namespace sf;
using namespace std;


class BackgroundMusic
{
private:
	Music* music;
public:
	int volume = 100;
	int number;
	BackgroundMusic();
	~BackgroundMusic();
	void change_background(string file_path);
	void set_volume(int volume);
	void start();
	void pause();
	void stop();
};

class Sounds
{
public:
	map<string, SoundBuffer*> buffers;
	map<string, double> volume{};
	map<string, double> constant_volume{};
	map<string, int> initial_volume{};

public:
	Sounds();
	~Sounds();
	void play_sound(string soundname);
	void add_sound(string soundname, string file_path, int volume);
	list<unique_ptr<Sound>>list1;
};
