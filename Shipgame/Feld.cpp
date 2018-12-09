#include "pch.h"
#include "Feld.h"


Feld::Feld()
{
	fieldstate = new FieldInfo();
}


Feld::~Feld()
{
}

void Feld::setPointerShip(Schiff * Ship)
{
	this->ship = Ship;
}
