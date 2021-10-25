#include "pch.h"
#include "InfoViewsComparator.h"

int InfoViewsComparator::compare(InfoMusica a, InfoMusica b)
{
	return a.getviews()- b.getviews();
}
