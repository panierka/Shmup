#include "SetVolume.h"

bool show_volume_interface = false;
int sound_volume = 5;
int music_volume = 5;
int general_volume = 5;

SetVolume::SetVolume()
{
	
}

SetVolume::~SetVolume()
{

}

void SetVolume::SetMainVolume(int new_volume)
{
	for (map<string, int>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		i->second = new_volume;
	}
	sound_volume = new_volume;
	general_volume = NAN;
}

void SetVolume::SetBackgroundVolume(int new_volume)
{
	background.set_volume(new_volume);
	music_volume = new_volume;
	general_volume = NAN;
}

void SetVolume::SetEntireVolume(int new_volume)
{
	SetMainVolume(new_volume);
	SetBackgroundVolume(new_volume);
	general_volume = new_volume;
}

void SetVolume::turn_up(int &volume)
{
	volume += 1;
	if (volume > 10)
		volume = 10;
	if (&volume == &sound_volume)
		SetMainVolume(volume);
	else if (&volume == &music_volume)
		SetBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}
void SetVolume::turn_down(int &volume)
{
	volume -= 1;
	if (volume < 0)
		volume = 0;
	if (&volume == &sound_volume)
		SetMainVolume(volume);
	else if (&volume == &music_volume)
		SetBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}