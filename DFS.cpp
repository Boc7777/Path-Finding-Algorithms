#include "DFS.h"
#include <iostream>


DFS::DFS(vector<vector<Cell>>& cell_tab_ref) : cell_tab(cell_tab_ref) {
	this->cell_tab = cell_tab;
	this->board_width = cell_tab[0].size();
	this->board_height = cell_tab.size();

	for (auto& cell_row : cell_tab) {
		for (auto& cell : cell_row) {
			if (cell.getStatus() == Enter) {
				this->head = &cell;
				break;
			}
		}
	}
}


vector<Direction> DFS::Check_Space_around(int x, int y) {
	vector<Direction> tab;
	//lewo
	if (x > 1) {
		if (cell_tab[y][x - 1].getStatus() == Drawed) {
			tab.push_back(Left);
		}
	}
	//prawo
	if (x < board_width - 2) {
		if (cell_tab[y][x + 1].getStatus() == Drawed) {
			tab.push_back(Right);
		}
	}
	//gora
	if (y > 1) {
		if (cell_tab[y - 1][x].getStatus() == Drawed) {
			tab.push_back(Top);
		}
	}
	//dol
	if (y < board_height - 2) {
		if (cell_tab[y + 1][x].getStatus() == Drawed) {
			tab.push_back(Bottom);
		}
	}

	return tab;
}

void DFS::Algorithm() {

	int x = head->getCoords().first;
	int y = head->getCoords().second;
	
	vector<Direction> tab_dir = Check_Space_around(x, y);

	if (!creatingPath) {
		if (tab_dir.size() != 0) {
			for (auto& dir : tab_dir) {
				last_tab.push_back(head);

				if (dir == Left) {
					head = &cell_tab[y][x - 2];
					if (head->getStatus() == Exit) {
						creatingPath = true;
					}
					cell_tab[y][x - 2].setStatus(Neighbour);
					cell_tab[y][x - 1].setStatus(Neighbour);
					last_tab.push_back(&cell_tab[y][x - 1]);
				}
				else if (dir == Bottom) {
					head = &cell_tab[y + 2][x];
					if (head->getStatus() == Exit) {
						creatingPath = true;
					}
					cell_tab[y + 2][x].setStatus(Neighbour);
					cell_tab[y + 1][x].setStatus(Neighbour);
					last_tab.push_back(&cell_tab[y+1][x]);
				}
				else if (dir == Right) {
					head = &cell_tab[y][x + 2];
					if (head->getStatus() == Exit) {
						creatingPath = true;
					}
					cell_tab[y][x + 2].setStatus(Neighbour);
					cell_tab[y][x + 1].setStatus(Neighbour);
					last_tab.push_back(&cell_tab[y][x + 1]);
				}
				else if (dir == Top) {
					head = &cell_tab[y - 2][x];
					if (head->getStatus() == Exit) {
						creatingPath = true;
					}
					cell_tab[y - 2][x].setStatus(Neighbour);
					cell_tab[y - 1][x].setStatus(Neighbour);
					last_tab.push_back(&cell_tab[y-1][x]);
				}
				break;
			}
		}
		else {
			head = last_tab[last_tab.size() - 1];
			last_tab.pop_back();
		}
	}
	else {
		
		
		if (last_tab.size() != 0) {
			last_tab[last_tab.size() - 1]->setStatus(Path);
			last_tab.pop_back();
		}
		else {
			generating = false;
		}


	}
	
	


	//lewo 
	//if (cell_tab[y][x - 2].getStatus() == Drawed && cell_tab[y][x - 1].getStatus() == Drawed) {
	//	if (x > 1){
	//		last_tab.push_back(head);
	//		head = &cell_tab[y][x - 2];
	//		cell_tab[y][x - 2].setStatus(Path);
	//		cell_tab[y][x - 1].setStatus(Path);
	//		cout << "lewo" << endl;

	//	}
	//}
	////prawo
	//else if (cell_tab[y][x + 2].getStatus() == Drawed && cell_tab[y][x + 1].getStatus() == Drawed) {
	//	if (x < board_width - 2) {
	//		last_tab.push_back(head);
	//		head = &cell_tab[y][x + 2];
	//		cell_tab[y][x + 2].setStatus(Path);
	//		cell_tab[y][x + 1].setStatus(Path);
	//		cout << "prawo" << endl;
	//	}
	//}
	////gora
	//else if (cell_tab[y - 2][x].getStatus() == Drawed && cell_tab[y - 1][x].getStatus() == Drawed) {
	//	if (y > 1) {
	//		last_tab.push_back(head);
	//		head = &cell_tab[y - 2][x];
	//		cell_tab[y-2][x].setStatus(Path);
	//		cell_tab[y-1][x].setStatus(Path);
	//		cout << "gora" << endl;
	//	}
	//}
	////dol
	//else if  (cell_tab[y + 2][x].getStatus() == Drawed && cell_tab[y + 1][x].getStatus() == Drawed) {
	//	if (y < board_height - 2) {
	//		last_tab.push_back(head);
	//		head = &cell_tab[y + 2][x];
	//		cell_tab[y][x + 2].setStatus(Path);
	//		cell_tab[y][x + 1].setStatus(Path);
	//		cout << "dol" << endl;
	//	}
	//}
}



bool DFS::getGeneratingStatus() {
	return generating;
}
