#include "SoundEffects.h"


BackgroundMusic::BackgroundMusic()
{
	music = make_shared<Music>();
}

void BackgroundMusic::change_background(string file_path)
{
	music->openFromFile(file_path); //d�wi�k odtwarzany bezpo�rednio z pliku
	music->setLoop(true);
	start();
}

//rozpoczyna od nowa lub wznawia muzyk� w tle
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

//ustawienie g�o�no�ci t�a
void BackgroundMusic::set_volume(int volume_level)
{
	volume = volume_level;
	music->setVolume(volume);
}

//ko�czy odtwarzanie d�wi�ku, nie zapisuje momentu przerwania odtwarzania
void BackgroundMusic::stop()
{
	music->stop();
}
Sounds::Sounds()
{

}

//usuni�cie bufor�w
Sounds::~Sounds()
{
	for (std::map<string, SoundBuffer*>::iterator i = buffers.begin(); i != buffers.end(); i++)
	{
		delete buffers[i->first];
	}
}

//odtwarzanie d�wi�ku 
void Sounds::play_sound(string soundname)
{
	unique_ptr<Sound> pointer = make_unique<Sound>(); //utworzenie wska�nika do obiektu klasy Sound
	pointer->setBuffer(*buffers[soundname]);
	pointer->setVolume(volume[soundname]);
	pointer->play();
	list1.push_back(move(pointer));	//umieszczenie wska�nika do obiektu Sound na ko�cu listy d�wi�k�w

	if(list1.size() >= 70)	//w momencie osi�gni�cia poziomu 70 obiekt�w na li�cie usuwany jest z niej pierwszy element, a wi�c najstarszy odtworzony d�wi�k
	{
		list1.pop_front();
	}
}

//dodanie d�wi�ku
void Sounds::add_sound(string soundname, string file_path, int sound_volume)
{
	buffers[soundname] = new SoundBuffer();	//dodanie nowego bufora do mapy
	buffers[soundname]->loadFromFile(file_path); //za�adowanie do bufora pliku d�wi�kowego
	volume[soundname] = sound_volume; //dodanie do mapy podanego poziomu g�o�no�ci
	constant_volume[soundname] = sound_volume; 
	initial_volume[soundname] = sound_volume;
}