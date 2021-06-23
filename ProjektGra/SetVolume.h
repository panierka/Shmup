#pragma once

#include "Classes.h"
#include <cmath>

extern bool show_volume_interface;
extern double sound_volume;
extern double music_volume;
extern double general_volume;
extern bool first_calculation;

//klasa do zmiany poziomu g³oœnoœci
class SetVolume
{
public:
	SetVolume();
	~SetVolume();
	void AddMainVolume(double new_volume);
	void SubtractMainVolume(double new_volume);
	void AddBackgroundVolume(double new_volume);
	void SubtractBackgroundVolume(double new_volume);
	void AddEntireVolume(double new_volume);
	void SetEntireVolume(double new_volume);
	void turn_up(double &volume);
	void turn_down(double &volume);
};