#pragma once
#include "Comparator.h"
#include "InfoMusica.h"
class InfoViewsComparator :
	public Comparator<InfoMusica>
{
	// Heredado v�a Comparator
	virtual int compare(InfoMusica a, InfoMusica b) override;
};

