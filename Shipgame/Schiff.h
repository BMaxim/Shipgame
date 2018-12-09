#pragma once
#include <string>
#include "pch.h"
using namespace std;
class Schiff
{
public:
	Schiff();
	~Schiff();
	string typ;
	int getShipSize();
	int kammer;
	bool Versenkt = false;
protected:
	int size;
	//int moeglicheAnzahl;
};

