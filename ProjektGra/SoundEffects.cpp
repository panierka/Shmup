#include "SoundEffects.h"


BackgroundMusic::BackgroundMusic()
{
	music = make_shared<Music>();
}

void BackgroundMusic::change_background(string file_path)
{
	music->openFromFile(file_path);
	music->setLoop(true);
	start();
}

void BackgroundMusic::start()
{
	music->play();
}

BackgroundMusic::~BackgroundMusic()
{

}

void BackgroundMusic::pause()
{
	music->pause();
}
void BackgroundMusic::set_volume(int volume_level)
{
	volume = volume_level;
	music->setVolume(volume);
}

void BackgroundMusic::stop()
{
	music->stop();
}
Sounds::Sounds()
{

}
Sounds::~Sounds()
{
	for (std::map<string, SoundBuffer*>::iterator i = buffers.begin(); i != buffers.end(); i++)
	{
		delete buffers[i->first];
	}
}
void Sounds::play_sound(string soundname)
{
	// ? 
	unique_ptr<Sound> pointer = make_unique<Sound>();
	pointer->setBuffer(*buffers[soundname]);
	pointer->setVolume(volume[soundname]);
	pointer->play();
	list1.push_back(move(pointer));

	if(list1.size() >= 70)
	{
		list1.pop_front();
	}
}
void Sounds::add_sound(string soundname, string file_path, int sound_volume)
{
	buffers[soundname] = new SoundBuffer();
	buffers[soundname]->loadFromFile(file_path);
	volume[soundname] = sound_volume;
	constant_volume[soundname] = sound_volume;
	initial_volume[soundname] = sound_volume;
}