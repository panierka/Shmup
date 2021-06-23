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

//funkcja do zwiêkszania poziomu dŸwiêków
void SetVolume::AddMainVolume(double new_volume)
{
	if (first_calculation_1)	//wejœcie do warunku tylko, gdy zmiana poziomu dŸwiêku odbywa siê po raz pierwszy
	{
		for (map<string, double>::iterator i = sound1.constant_volume.begin(); i != sound1.constant_volume.end(); i++) 
		{
			i->second *= 0.1; //wyznaczenie 10% g³oœnoœci wyjœciowej dla ka¿dego dŸwiêku - pêtla
		}
		first_calculation_1 = false;
	}
	bool check = false;
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (i->second + sound1.constant_volume[i->first] >= sound1.initial_volume[i->first]) //sprawdzenie, czy po zwiêkszeniu poziomu g³oœnoœci dla jakiegokolwiek dŸwiêku zostanie przekroczony punkt maksymalny
		{
			check = true;
			break;
		}
	}
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (check) //je¿eli przekroczony zosta³ punkt maksymalny, poziom g³oœnoœci zostaje ustawiony na poziom maksymalny
			sound1.volume[i->first] = sound1.initial_volume[i->first];
		else //w przeciwnym wypadku g³oœnoœæ zwiêkszana jest o 10%
			i->second += sound1.constant_volume[i->first];
	}
			
}

//funkcja do zmniejszania poziomu dŸwiêków
void SetVolume::SubtractMainVolume(double new_volume)
{
	if (first_calculation_1) //wejœcie do warunku tylko, gdy zmiana poziomu dŸwiêku odbywa siê po raz pierwszy
	{
		for (map<string, double>::iterator i = sound1.constant_volume.begin(); i != sound1.constant_volume.end(); i++)
		{
			i->second *= 0.1; //wyznaczenie 10% g³oœnoœci wyjœciowej dla ka¿dego dŸwiêku - pêtla
		}
		first_calculation_1 = false;
	}
	bool check = false;
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (i->second - sound1.constant_volume[i->first] < 0) //sprawdzenie, czy po zmniejszeniu poziomu g³oœnoœci dla jakiegokolwiek dŸwiêku zostanie przekroczony punkt minimalny
		{
			check = true;
			break;
		}
	}
	for (map<string, double>::iterator i = sound1.volume.begin(); i != sound1.volume.end(); i++)
	{
		if (check) //je¿eli przekroczony zosta³ punkt minimalny, poziom g³oœnoœci zostaje ustawiony na poziom minimalny
			sound1.volume[i->first] = 0;
		else //w przeciwnym wypadku g³oœnoœæ zmniejszana jest o 10%
			i->second -= sound1.constant_volume[i->first];
	}

}

//funkcja do zwiêkszania poziomu g³oœnoœci muzyki w tle
void SetVolume::AddBackgroundVolume(double new_volume)
{
	if (first_calculation) //wejœcie do warunku tylko, gdy zmiana poziomu t³a odbywa siê po raz pierwszy
	{
		for (int i = 0; i < 4; i++)
		{
			tab[i]->number = tab[i]->volume * 0.1; //wyznaczenie 10% g³oœnoœci wyjœciowej dla ka¿dego t³a - pêtla
		}
		first_calculation = false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (tab[i]->volume + tab[i]->number <= 100) //je¿eli zmiana g³oœnoœci nie powoduje przekroczenia punktu maksymalnego, g³oœnoœæ ustawiana jest na ¿¹dan¹ wartoœæ
			tab[i]->set_volume(tab[i]->volume + tab[i]->number);
		else //w przeciwnym wypadku, g³oœnoœæ ustawiana jest na wartoœæ maksymaln¹
			tab[i]->set_volume(100);
	}
}

//funkcja do zmniejszenia poziomu g³oœnoœci muzyki w tle
void SetVolume::SubtractBackgroundVolume(double new_volume)
{
	if (first_calculation) //wejœcie do warunku tylko, gdy zmiana poziomu t³a odbywa siê po raz pierwszy
	{
		for (int i = 0; i < 4; i++)
		{
			tab[i]->number = tab[i]->volume * 0.1; //wyznaczenie 10% g³oœnoœci wyjœciowej dla ka¿dego t³a - pêtla
		}
		first_calculation = false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (tab[i]->volume - tab[i]->number >= 0) //je¿eli zmiana g³oœnoœci nie powoduje przekroczenia punktu minimalnego, g³oœnoœæ ustawiana jest na ¿¹dan¹ wartoœæ
			tab[i]->set_volume(tab[i]->volume - tab[i]->number);
		else //w przeciwnym wypadku, g³oœnoœæ ustawiana jest na wartoœæ minimaln¹
			tab[i]->set_volume(0);
	}
}

//ustawienie g³oœnoœci globalnej (t³o + dŸwiêki)
void SetVolume::SetEntireVolume(double new_volume) 
{
	Listener::setGlobalVolume(new_volume*10); //wykorzystanie klasy Listener i jej metody do ustawienia g³oœnoœci globalnej
}

//funkcja do zwiêkszenia g³oœnoœci - przekazywany parametr odpowiedniej g³oœnoœci (dŸwiêku, t³a lub globalnej)
void SetVolume::turn_up(double &volume)
{
	volume += 1; 
	if (volume > 10)
		volume = 10;
	if (&volume == &sound_volume) //wywo³anie odpowiedniej funkcji 
		AddMainVolume(volume);
	else if (&volume == &music_volume)
		AddBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}

//funkcja do zmniejszenia g³oœnoœci - przekazywany parametr odpowiedniej g³oœnoœci (dŸwiêku, t³a lub globalnej)
void SetVolume::turn_down(double& volume)
{
	volume -= 1;
	if (volume < 0)
		volume = 0;
	if (&volume == &sound_volume) //wywo³anie odpowiedniej funkcji
		SubtractMainVolume(volume);
	else if (&volume == &music_volume)
		SubtractBackgroundVolume(volume);
	else if (&volume == &general_volume)
		SetEntireVolume(volume);
}