#include "Cell.h"
#include "Board.h"
#include "Dijkstra.h"
#include <string>
#include <iostream>


using namespace std;

Board::Board(float cell_size, int board_width, int board_height, RenderWindow* window) {
	this->cell_size = cell_size;
	this->board_width = board_width;
	this->board_height = board_height;
	this->window = window;
	
	for (int y = 0;y < board_height;y++) {
		vector<Cell> row;
		for (int x = 0; x < board_width;x++) {
			row.push_back(Cell(x,y,cell_size));
		}
		cell_tab.push_back(row);
		row.clear();
	}

	srand(time(0));

	Draw_Random_Cell();
	/*for (int y = 0;y < board_height;y++) {
		for (int x = 0; x < board_width;x++) {
			if (x % 2 == 1 && y % 2 == 1) {
				cell_tab[y][x].setStatus(Drawed);
			}
		}
	}*/
}

void Board::DrawBoard() {
	for (auto& cell_row : cell_tab) {
		for (auto& cell : cell_row) {
			window->draw(cell);
		}
	}
}

bool Board::getGeneratingStatus() {
	return generating;
}

void Board::ChooseEnterAndExit() {
	bool found_en = false;
	int x_en;
	int y_en;
	while (!found_en) {
		x_en = rand() % board_width;
		y_en = rand() % board_height;
		if (cell_tab[y_en][x_en].getStatus() == Drawed && x_en %2 ==1 && y_en %2 == 1) {
			found_en = true;
			cell_tab[y_en][x_en].setStatus(Enter);
		}
	}
	bool found_ex = false;
	int x_ex;
	int y_ex;
	while (!found_ex) {
		x_ex = rand() % board_width;
		y_ex = rand() % board_height;
		if (cell_tab[y_ex][x_ex].getStatus() == Drawed && x_ex % 2 == 1 && y_ex % 2 == 1 &&pow(pow(x_ex - x_en,2)+ pow(y_ex - y_en,2),0.5f)>0.5f * pow(pow(board_width,2)+pow(board_height,2),0.5f)){
			found_ex = true;
			cell_tab[y_ex][x_ex].setStatus(Exit);
			
		}
	}
}



//universal functions 
vector<Direction> Board::Check_Space_around(int x, int y) {
	vector<Direction> tab;
	//lewo
	if (x > 1) {
		if (cell_tab[y][x - 2].getStatus() == Other) {
			tab.push_back(Left);
		}
	}
	//prawo
	if (x < board_width - 2) {
		if (cell_tab[y][x + 2].getStatus() == Other) {
			tab.push_back(Right);
		}
	}
	//gora
	if (y > 1) {
		if (cell_tab[y - 2][x].getStatus() == Other) {
			tab.push_back(Top);
		}
	}
	//dol
	if (y < board_height - 2) {
		if (cell_tab[y + 2][x].getStatus() == Other) {
			tab.push_back(Bottom);
		}
	}

	return tab;
}

void Board::Update_Head(Cell* cell) {
	head_hak = cell;
}

void Board::Draw_Random_Cell() {
	int x = (rand() % (board_width - 2)) + 2;
	int y = (rand() % (board_height - 2)) + 2;
	if (x % 2 == 0) {
		x -= 1;
	}
	if (y % 2 == 0) {
		y -= 1;
	}

	cell_tab[y][x].setStatus(Drawed);

	head_hak = &cell_tab[y][x];
}


//Depth-First search
vector<vector<Cell>>& Board::Depth_First_search_CreateMaze() {
	while (generating) {
		int cell_x = head_hak->getCoords().first;
		int cell_y = head_hak->getCoords().second;
		vector<Direction> Dir_tab = Check_Space_around(cell_x, cell_y);

		if (Dir_tab.size() > 0) {
			int randomDir = rand() % Dir_tab.size();
			Direction Choosen_Dir = Dir_tab[randomDir];



			if (Choosen_Dir == Left) {
				cell_tab[cell_y][cell_x - 1].setStatus(Neighbour);
				cell_tab[cell_y][cell_x - 2].setStatus(Neighbour);

				neighbours_cells.push_back(&cell_tab[cell_y][cell_x - 1]);
				neighbours_cells.push_back(&cell_tab[cell_y][cell_x - 2]);

				Update_Head(&cell_tab[cell_y][cell_x - 2]);
			}
			else if (Choosen_Dir == Right) {
				cell_tab[cell_y][cell_x + 1].setStatus(Neighbour);
				cell_tab[cell_y][cell_x + 2].setStatus(Neighbour);

				neighbours_cells.push_back(&cell_tab[cell_y][cell_x + 1]);
				neighbours_cells.push_back(&cell_tab[cell_y][cell_x + 2]);

				Update_Head(&cell_tab[cell_y][cell_x + 2]);
			}
			else if (Choosen_Dir == Top) {
				cell_tab[cell_y - 1][cell_x].setStatus(Neighbour);
				cell_tab[cell_y - 2][cell_x].setStatus(Neighbour);

				neighbours_cells.push_back(&cell_tab[cell_y - 1][cell_x]);
				neighbours_cells.push_back(&cell_tab[cell_y - 2][cell_x]);

				Update_Head(&cell_tab[cell_y - 2][cell_x]);
			}
			else if (Choosen_Dir == Bottom) {
				cell_tab[cell_y + 1][cell_x].setStatus(Neighbour);
				cell_tab[cell_y + 2][cell_x].setStatus(Neighbour);

				neighbours_cells.push_back(&cell_tab[cell_y + 1][cell_x]);
				neighbours_cells.push_back(&cell_tab[cell_y + 2][cell_x]);

				Update_Head(&cell_tab[cell_y + 2][cell_x]);
			}


		}

		else {
			if (neighbours_cells.size() > 0) {
				Cell* last_cell = neighbours_cells[neighbours_cells.size() - 1];
				Cell* last_bridge = neighbours_cells[neighbours_cells.size() - 2];

				head_hak->setStatus(Drawed);
				last_cell->setStatus(Drawed);
				last_bridge->setStatus(Drawed);


				if (Check_Space_around(last_cell->getCoords().first, last_cell->getCoords().second).size() > 0) {
					Update_Head(last_cell);
				}
				else {
					neighbours_cells.pop_back();
					neighbours_cells.pop_back();
				}
			}
			else {
				generating = false;
				ChooseEnterAndExit();
			}

		}
	}
	return cell_tab;
}
