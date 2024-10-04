#pragma once
#include "vector"
#include "Cell.h"
#include "Board.h"


class DFS
{
public:
	DFS(vector<vector<Cell>>& cell_tab_ref);

	void Algorithm();

	bool getGeneratingStatus();

	vector<Direction> Check_Space_around(int x, int y);

	void CreatePath();

private:

	vector<vector<Cell>>& cell_tab;
	bool generating = true;
	bool creatingPath = false;
	vector<Cell*> last_tab; 
	Cell* head;

	int board_width;
	int board_height;


};

