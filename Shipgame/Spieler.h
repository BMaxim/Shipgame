#pragma once
#include "Grid.h"
#include <vector>
#include "Schiff.h"
using namespace std;
class Spieler
{
public:
	Spieler();
	~Spieler();
	Grid own;
	Grid enemy;
	vector<Schiff> freieSchiffe;
	string name;
	bool spielerAlive();
	bool platziereSchiff(int x, int y);
};

