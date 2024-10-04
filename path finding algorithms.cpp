#include <iostream>
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Dijkstra.h"
#include "DFS.h"

using namespace std;
using namespace sf;


const float cell_size = 10.f;
const int width_in_cells = 101;
const int height_in_cells = 101;


unsigned display_width = cell_size * width_in_cells;
unsigned display_height = cell_size * height_in_cells;



int main()
{
    RenderWindow window(VideoMode(display_width, display_height), "Maze");
    //window.setFramerateLimit(7);

    Event event;
    Board board(cell_size, width_in_cells, height_in_cells, &window);

    vector<vector<Cell>>& cell_tab = board.Depth_First_search_CreateMaze();
    
    Dijkstra dijkstra(cell_tab);
    DFS dfs(cell_tab);

    while (window.isOpen()) {
        window.clear(Color::Black);

        if (dijkstra.getGeneratingStatus()) {
            //dijkstra.Algorithm();
            dfs.Algorithm();
        }
   
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }
        board.DrawBoard();
        window.display();
    }
}


