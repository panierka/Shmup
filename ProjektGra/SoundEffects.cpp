#include "SoundEffects.h"


BackgroundMusic::BackgroundMusic()
{
	music = make_shared<Music>();
}

void BackgroundMusic::change_background(string file_path)
{
	music->openFromFile(file_path); //dŸwiêk odtwarzany bezpoœrednio z pliku
	music->setLoop(true);
	start();
}

//rozpoczyna od nowa lub wznawia muzykê w tle
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

//ustawienie g³oœnoœci t³a
void BackgroundMusic::set_volume(int volume_level)
{
	volume = volume_level;
	music->setVolume(volume);
}

//koñczy odtwarzanie dŸwiêku, nie zapisuje momentu przerwania odtwarzania
void BackgroundMusic::stop()
{
	music->stop();
}
Sounds::Sounds()
{

}

//usuniêcie buforów
Sounds::~Sounds()
{
	for (std::map<string, SoundBuffer*>::iterator i = buffers.begin(); i != buffers.end(); i++)
	{
		delete buffers[i->first];
	}
}

//odtwarzanie dŸwiêku 
void Sounds::play_sound(string soundname)
{
	unique_ptr<Sound> pointer = make_unique<Sound>(); //utworzenie wskaŸnika do obiektu klasy Sound
	pointer->setBuffer(*buffers[soundname]);
	pointer->setVolume(volume[soundname]);
	pointer->play();
	list1.push_back(move(pointer));	//umieszczenie wskaŸnika do obiektu Sound na koñcu listy dŸwiêków

	if(list1.size() >= 70)	//w momencie osi¹gniêcia poziomu 70 obiektów na liœcie usuwany jest z niej pierwszy element, a wiêc najstarszy odtworzony dŸwiêk
	{
		list1.pop_front();
	}
}

//dodanie dŸwiêku
void Sounds::add_sound(string soundname, string file_path, int sound_volume)
{
	buffers[soundname] = new SoundBuffer();	//dodanie nowego bufora do mapy
	buffers[soundname]->loadFromFile(file_path); //za³adowanie do bufora pliku dŸwiêkowego
	volume[soundname] = sound_volume; //dodanie do mapy podanego poziomu g³oœnoœci
	constant_volume[soundname] = sound_volume; 
	initial_volume[soundname] = sound_volume;
}