#pragma once
#include"FieldInfo.h"
#include"Schiff.h"
class Feld
{
public:
	Feld();
	~Feld();
			//Aufruf funktioniert noch nicht
	/*char empty = ' ';*/			//Darum in der Klasse provisorisch init.
	//	SchiffOk = 'V',
	//	SchiffHit = 'X',
	//	shoot = 'o',
	//	destroyed = '*';
	//FieldInfo::fieldState state = FieldInfo::empty;
	FieldInfo* fieldstate;
	void setPointerShip(Schiff* Ship);

	Schiff* ship;

};

