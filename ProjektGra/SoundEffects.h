#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>
using namespace sf;
using namespace std;


class BackgroundMusic
{
private:
	int volume = 10;
	Music* music;
public:
	BackgroundMusic();
	~BackgroundMusic();
	void set_volume(int volume);
	void start();
	void pause();
};

class Sounds
{
public:
	map<string, SoundBuffer*> buffers;
	map<string, int> volume;
private:
	Sound* sound;
public:
	Sounds();
	~Sounds();
	void play_sound(string soundname);
	void add_sound(string soundname, string file_path, int volume);
};