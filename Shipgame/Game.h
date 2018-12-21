#pragma once
#include "pch.h"
#include"Spieler.h"
#include<iostream>
#include <string>
#include<vector>
#include"Grid.h"
#include "FregatteSchiff.h"
#include "KreuzerSchiff.h"
#include "Schiff.h"
#include "time.h"
#define anzahlBoote 1

using namespace std;

class Game
{
public:
	Game();
	~Game();
	Spieler S1;
	Spieler S2;
	
	void init();
	int trefferZeile = -1;					//global, für Compuetermodus, wenn er ein Treffer erzielt
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
	char umwandlungCompYAchse(int Y);
	int intEinlesen();
	char charEinlesen();
	void update(Grid* Netz);
	Grid S1ownNetz;
	Grid S1enemyNetz;
	Grid S2ownNetz;
	Grid S2enemyNetz;
	void setShipComputer(string spielerName, Grid* netz);
};

