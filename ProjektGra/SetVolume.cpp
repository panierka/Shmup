#include "SetVolume.h"

bool first_calculation = true;
bool first_calculation_1 = true;
bool show_volume_interface = false;
double sound_volume = 10;
double music_volume = 10;
double general_volume = 10;
double general_faction_for_background;
double general_faction_for_sounds;

SetVolume::SetVolume()
{
	
}

SetVolume::~SetVolume()
{

}

void SetVolume::AddMainVolume(double new_volume)
{
	if (first_calculation_1)
	{
		for (map<string, double>::iterator i = sound1.constant_volume.begin(); i != sound1.constant_volume.end(); i++)
		{
			i->second *= 0.1;
		}
		first_calculation_1 = false;
	}
	bool check = false;
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (i->second + sound1.constant_volume[i->first] >= sound1.initial_volume[i->first])
		{
			check = true;
			break;
		}
	}
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (check)
			sound1.volume[i->first] = sound1.initial_volume[i->first];
		else
			i->second += sound1.constant_volume[i->first];
	}
			
}

void SetVolume::SubtractMainVolume(double new_volume)
{
	if (first_calculation_1)
	{
		for (map<string, double>::iterator i = sound1.constant_volume.begin(); i != sound1.constant_volume.end(); i++)
		{
			i->second *= 0.1;
		}
		first_calculation_1 = false;
	}
	bool check = false;
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (i->second - sound1.constant_volume[i->first] < 0)
		{
			check = true;
			break;
		}
	}
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (check)
			sound1.volume[i->first] = 0;
		else
			i->second -= sound1.constant_volume[i->first];
	}

}

void SetVolume::AddBackgroundVolume(double new_volume)
{
	if (first_calculation)
	{
		background.number = background.volume * 0.1;
		first_calculation = false;
	}
	if (background.volume + background.number <= 90)
		background.set_volume(background.volume + background.number);
	else
		background.set_volume(90);
}

void SetVolume::SubtractBackgroundVolume(double new_volume)
{
	if (first_calculation)
	{
		background.number =  background.volume * 0.1;
		first_calculation = false;
	}
	if (background.volume - background.number >= 0)
		background.set_volume(background.volume - background.number);
	else
		background.set_volume(0);
}

void SetVolume::SetEntireVolume(double new_volume)
{
	Listener::setGlobalVolume(new_volume*10);
}

void SetVolume::turn_up(double &volume)
{
	volume += 1;
	if (volume > 10)
		volume = 10;
	if (&volume == &sound_volume)
		AddMainVolume(volume);
	else if (&volume == &music_volume)
		AddBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}
void SetVolume::turn_down(double& volume)
{
	volume -= 1;
	if (volume < 0)
		volume = 0;
	if (&volume == &sound_volume)
		SubtractMainVolume(volume);
	else if (&volume == &music_volume)
		SubtractBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}