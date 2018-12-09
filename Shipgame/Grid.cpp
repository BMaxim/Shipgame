#include "pch.h"
#include "Grid.h"


Grid::Grid()
{

	for (int i = 0; i < Fieldsize; i++) {
		vector<Feld*> Zeile;
		for (int j = 0; j < Fieldsize; j++) {
			Feld* Reihe = new Feld();
	
			Zeile.push_back(Reihe);
		}
		this->vMatrix.push_back(Zeile);
	}
}

Grid::~Grid()
{
}
