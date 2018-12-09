#pragma once
#include"pch.h"
#include<stdlib.h>
class FieldInfo
{
public:
	FieldInfo();
	~FieldInfo();
	
	char getState();
	void setStateShoot();
	void setStateShip();
	void canSetStateShip();
	void setStateWater(bool Treffer);
	void setStateDestroyed();
private:
	
	char empty = ' ',
		SchiffOk = 'V',
		SchiffHit = 'X',
		shoot = 'o',
		destroyed = '*';
	char state = empty;
};

