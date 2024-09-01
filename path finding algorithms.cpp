#include <iostream>
#include "SFML/Graphics.hpp"
#include "Board.h"


using namespace std;
using namespace sf;


const float cell_size = 40.f;
const int width_in_cells = 20;
const int height_in_cells = 20;


unsigned display_width = cell_size * width_in_cells;
unsigned display_height = cell_size * height_in_cells;

vector<vector<Cell>> cell_tab;

int main()
{
    RenderWindow window(VideoMode(display_width, display_height), "Maze");
    //window.setFramerateLimit(30);

    Event event;
    Board board(cell_size, width_in_cells, height_in_cells, &window);

    while (window.isOpen()) {
        window.clear(Color::Black);


        if (board.getGeneratingStatus()) {
            cell_tab=board.Depth_First_search_CreateMaze();
        }
        cell_tab[1][1].setStatus(Neighbour);
        

        board.DrawBoard();

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.display();
    }
}


