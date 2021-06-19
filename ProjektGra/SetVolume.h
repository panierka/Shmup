#pragma once

#include "Classes.h"

extern bool show_volume_interface;
extern int sound_volume;
extern int music_volume;
extern int general_volume;

class SetVolume
{
public:
	SetVolume();
	~SetVolume();
	void SetMainVolume(int new_volume);
	void SetBackgroundVolume(int new_volume);
	void SetEntireVolume(int new_volume);
	void turn_up(int &volume);
	void turn_down(int &volume);
};