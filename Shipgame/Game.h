#pragma once
#include "pch.h"
#include"Spieler.h"
#include<iostream>
#include <string>
#include<vector>
#include"Grid.h"
#include "FregatteSchiff.h"
#include "KreuzerSchiff.h"
#include "Schiff.h";
#define anzahlBoote 2

using namespace std;

class Game
{
public:
	Game();
	~Game();
	Spieler S1;
	Spieler S2;
	
	void init();

	void play();
	void fire(Grid* own, Grid* enemy,int X,int Y);
	void gameOver(Grid* Netz);
	void copyRight();
	void strichLinie();

private:
	void printField(string spielerName, Grid Netz);
	void setShip(string spielerName, Grid* netz);
	void setShipField(Schiff* meinSchiff, int X,int Y,Grid* meinNetz);
	int umwandlungYAchse(char Y);
	int intEinlesen();
	char charEinlesen();
	void update(Grid* Netz);
	Grid S1ownNetz;
	Grid S1enemyNetz;
	Grid S2ownNetz;
	Grid S2enemyNetz;
};

