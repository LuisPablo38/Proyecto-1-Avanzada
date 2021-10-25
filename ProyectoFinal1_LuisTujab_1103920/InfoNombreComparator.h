#pragma once
#include "Comparator.h"
#include"InfoMusica.h"
#include<string>

using std::string;

class InfoNombreComparator :
	public Comparator<InfoMusica>
{
public:
	// Heredado vía Comparator
	virtual int compare(InfoMusica a, InfoMusica b)
	{
		return a.getnombreCan().compare(b.getnombreCan());
	}
};

