#include "pch.h"
#include "InfoMusica.h"

InfoMusica::InfoMusica(int id, string nombreCan, double views)
{
	this->id = id;
	this->nombreCan = nombreCan;
	this->views = views;
}


double InfoMusica::getviews()
{
	return this->views;
}

string InfoMusica::getnombreCan()
{
	return this->nombreCan;
}

int InfoMusica::getid()
{
	return this->id;
}
