#pragma once

void print(std::string _message)
{
	cout << _message << endl;
}


int random_number(int _min, int _max)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution <int> distribution(_min, _max);
	return distribution(generator);
}

template<typename T>
T random_object(T* _array, int _len)
{
	return _array[random_number(0, _len)];
}