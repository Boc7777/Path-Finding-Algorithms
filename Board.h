#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include "Cell.h"

using namespace sf; 
using namespace std;

enum Direction {
	Left,
	Right,
	Top,
	Bottom,
	Nothing
};

class Board
{
public: 
	Board(float cell_size, int board_width, int board_height, RenderWindow* window);
	
	void DrawBoard();
	bool getGeneratingStatus();


	vector<vector<Cell>>& Depth_First_search_CreateMaze();
	void ChooseEnterAndExit();

	
private:

	//universal functions
	vector<Direction> Check_Space_around(int x, int y);
	void Update_Head(Cell* cell);
	void Draw_Random_Cell();

	vector<vector<Cell>> cell_tab;
	vector<Cell*> neighbours_cells;

	Cell* head_hak;

	RenderWindow* window;
	bool generating = true;
	float cell_size;
	int board_width;
	int board_height;
};

