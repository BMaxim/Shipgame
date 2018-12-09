#include "pch.h"
#include "FieldInfo.h"


FieldInfo::FieldInfo()
{
}


FieldInfo::~FieldInfo()
{
}

char FieldInfo::getState()
{
	return this->state;
}

void FieldInfo::setStateShoot()		//Wenn geschossen wird
{
	if (state == empty) {
		this->state = shoot;
		//throw "Schuss ging ins Wasser!";
	}
	else if (state == SchiffOk) {
		this->state = SchiffHit;
		throw "Schiff getroffen!";
	}
}

void FieldInfo::setStateShip()
{
	if (state == empty) {
		state = SchiffOk;
	}
	else if(state == SchiffOk) {
		throw "Hier ist schon ein Schiff plaziert!";
	}
}

void FieldInfo::canSetStateShip()
{
	if (state == SchiffOk) {
		throw "Hier ist schon ein Schiff plaziert!";
	}
}

void FieldInfo::setStateWater(bool Treffer)
{
	if (Treffer == false) {
		this->state = shoot;
	}
	else if (Treffer == true) {
		this->state = SchiffHit;
	}

}

void FieldInfo::setStateDestroyed()
{
	this->state = this->destroyed;
}
