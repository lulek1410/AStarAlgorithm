#pragma once
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "astar.hpp"

class MainWindow
{
private:
	sf::RenderWindow window;
	std::shared_ptr<Astar> astar;
	bool is_setting_start, is_setting_end;
	bool is_searching;
	Grid grid;
	void run();
	void handleEvents();
	bool mouseInsideWindow(sf::Vector2i mousePos);
	void handleClickEvent(int row, int col);
	void setStart(int row, int col);
	void setEnd(int row, int col);
	void update();
	void draw();
	int selected_row, selected_col;
public:
	MainWindow();
};

