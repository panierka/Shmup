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

//funkcja do zwi�kszania poziomu d�wi�k�w
void SetVolume::AddMainVolume(double new_volume)
{
	if (first_calculation_1)	//wej�cie do warunku tylko, gdy zmiana poziomu d�wi�ku odbywa si� po raz pierwszy
	{
		for (map<string, double>::iterator i = sound1.constant_volume.begin(); i != sound1.constant_volume.end(); i++) 
		{
			i->second *= 0.1; //wyznaczenie 10% g�o�no�ci wyj�ciowej dla ka�dego d�wi�ku - p�tla
		}
		first_calculation_1 = false;
	}
	bool check = false;
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (i->second + sound1.constant_volume[i->first] >= sound1.initial_volume[i->first]) //sprawdzenie, czy po zwi�kszeniu poziomu g�o�no�ci dla jakiegokolwiek d�wi�ku zostanie przekroczony punkt maksymalny
		{
			check = true;
			break;
		}
	}
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (check) //je�eli przekroczony zosta� punkt maksymalny, poziom g�o�no�ci zostaje ustawiony na poziom maksymalny
			sound1.volume[i->first] = sound1.initial_volume[i->first];
		else //w przeciwnym wypadku g�o�no�� zwi�kszana jest o 10%
			i->second += sound1.constant_volume[i->first];
	}
			
}

//funkcja do zmniejszania poziomu d�wi�k�w
void SetVolume::SubtractMainVolume(double new_volume)
{
	if (first_calculation_1) //wej�cie do warunku tylko, gdy zmiana poziomu d�wi�ku odbywa si� po raz pierwszy
	{
		for (map<string, double>::iterator i = sound1.constant_volume.begin(); i != sound1.constant_volume.end(); i++)
		{
			i->second *= 0.1; //wyznaczenie 10% g�o�no�ci wyj�ciowej dla ka�dego d�wi�ku - p�tla
		}
		first_calculation_1 = false;
	}
	bool check = false;
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (i->second - sound1.constant_volume[i->first] < 0) //sprawdzenie, czy po zmniejszeniu poziomu g�o�no�ci dla jakiegokolwiek d�wi�ku zostanie przekroczony punkt minimalny
		{
			check = true;
			break;
		}
	}
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (check) //je�eli przekroczony zosta� punkt minimalny, poziom g�o�no�ci zostaje ustawiony na poziom minimalny
			sound1.volume[i->first] = 0;
		else //w przeciwnym wypadku g�o�no�� zmniejszana jest o 10%
			i->second -= sound1.constant_volume[i->first];
	}

}

//funkcja do zwi�kszania poziomu g�o�no�ci muzyki w tle
void SetVolume::AddBackgroundVolume(double new_volume)
{
	if (first_calculation) //wej�cie do warunku tylko, gdy zmiana poziomu t�a odbywa si� po raz pierwszy
	{
		for (int i = 0; i < 4; i++)
		{
			tab[i]->number = tab[i]->volume * 0.1; //wyznaczenie 10% g�o�no�ci wyj�ciowej dla ka�dego t�a - p�tla
		}
		first_calculation = false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (tab[i]->volume + tab[i]->number <= 100) //je�eli zmiana g�o�no�ci nie powoduje przekroczenia punktu maksymalnego, g�o�no�� ustawiana jest na ��dan� warto��
			tab[i]->set_volume(tab[i]->volume + tab[i]->number);
		else //w przeciwnym wypadku, g�o�no�� ustawiana jest na warto�� maksymaln�
			tab[i]->set_volume(100);
	}
}

//funkcja do zmniejszenia poziomu g�o�no�ci muzyki w tle
void SetVolume::SubtractBackgroundVolume(double new_volume)
{
	if (first_calculation) //wej�cie do warunku tylko, gdy zmiana poziomu t�a odbywa si� po raz pierwszy
	{
		for (int i = 0; i < 4; i++)
		{
			tab[i]->number = tab[i]->volume * 0.1; //wyznaczenie 10% g�o�no�ci wyj�ciowej dla ka�dego t�a - p�tla
		}
		first_calculation = false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (tab[i]->volume - tab[i]->number >= 0) //je�eli zmiana g�o�no�ci nie powoduje przekroczenia punktu minimalnego, g�o�no�� ustawiana jest na ��dan� warto��
			tab[i]->set_volume(tab[i]->volume - tab[i]->number);
		else //w przeciwnym wypadku, g�o�no�� ustawiana jest na warto�� minimaln�
			tab[i]->set_volume(0);
	}
}

//ustawienie g�o�no�ci globalnej (t�o + d�wi�ki)
void SetVolume::SetEntireVolume(double new_volume) 
{
	Listener::setGlobalVolume(new_volume*10); //wykorzystanie klasy Listener i jej metody do ustawienia g�o�no�ci globalnej
}

//funkcja do zwi�kszenia g�o�no�ci - przekazywany parametr odpowiedniej g�o�no�ci (d�wi�ku, t�a lub globalnej)
void SetVolume::turn_up(double &volume)
{
	volume += 1; 
	if (volume > 10)
		volume = 10;
	if (&volume == &sound_volume) //wywo�anie odpowiedniej funkcji 
		AddMainVolume(volume);
	else if (&volume == &music_volume)
		AddBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}

//funkcja do zmniejszenia g�o�no�ci - przekazywany parametr odpowiedniej g�o�no�ci (d�wi�ku, t�a lub globalnej)
void SetVolume::turn_down(double& volume)
{
	volume -= 1;
	if (volume < 0)
		volume = 0;
	if (&volume == &sound_volume) //wywo�anie odpowiedniej funkcji
		SubtractMainVolume(volume);
	else if (&volume == &music_volume)
		SubtractBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}