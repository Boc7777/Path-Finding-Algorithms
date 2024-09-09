#pragma once
#include "vector"
#include "Cell.h"

class Dijkstra
{
public:
	Dijkstra(vector<vector<Cell>>& cell_tab_ref);

	void Algorithm();

	bool getGeneratingStatus();


private:
	vector<vector<Cell>>& cell_tab;
	bool generating = true; 
};

