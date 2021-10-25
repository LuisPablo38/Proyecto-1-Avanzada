#pragma once
#include <string>

using std::string; 
class InfoMusica
{
	int id;
	string nombreCan;
	double views;

public:
	InfoMusica( int id, string nombreCan, double views);

	int getid();
	string getnombreCan();
	double getviews();
};