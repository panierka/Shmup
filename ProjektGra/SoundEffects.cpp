#include "SoundEffects.h"


BackgroundMusic::BackgroundMusic()
{
	music = new Music();
	music->openFromFile("../Assets/Sounds/Soundtrack.wav");
	music->setLoop(true);
	music->setVolume(volume);
	start();
}
BackgroundMusic::~BackgroundMusic()
{
	delete music;
}
void BackgroundMusic::start()
{
	music->play();
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
Sounds::Sounds()
{

}
Sounds::~Sounds()
{
	delete sound;
	for (std::map<string, SoundBuffer*>::iterator i = buffers.begin(); i != buffers.end(); i++)
	{
		delete buffers[i->first];
	}
}
void Sounds::play_sound(string soundname)
{
	// ? 
	Sound* sound = new Sound();
	sound->setBuffer(*buffers[soundname]);
	sound->setVolume(volume[soundname]);
	sound->play();
}
void Sounds::add_sound(string soundname, string file_path, int sound_volume)
{
	buffers[soundname] = new SoundBuffer();
	buffers[soundname]->loadFromFile(file_path);
	volume[soundname] = sound_volume;
	constant_volume[soundname] = sound_volume;
	initial_volume[soundname] = sound_volume;
}