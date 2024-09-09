#include "Dijkstra.h"


Dijkstra::Dijkstra(vector<vector<Cell>>& cell_tab_ref) : cell_tab(cell_tab_ref){
	this->cell_tab = cell_tab;
}

void Dijkstra::Algorithm() {
	
}

bool Dijkstra::getGeneratingStatus() {
	return generating;
}
