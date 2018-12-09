#pragma once
#include "pch.h"
#include<vector>
#include<iostream>
#include"Feld.h"
using namespace std;
#define Fieldsize 10

class Grid
{
public:
	Grid();
	~Grid();
	vector<vector<Feld*>> vMatrix;
};

