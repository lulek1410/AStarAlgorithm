#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
private:
	sf::RectangleShape rect;
public:
	std::shared_ptr<Cell> parrent;
	Cell(sf::Vector2i position, sf::Vector2f size, sf::Vector2i rowcol);
	bool is_obstacle;
	bool is_starting, is_end;
	bool is_closed, is_open;
	bool is_path;
	int row, col;
	double f, g, h;
	void update();
	void draw(sf::RenderWindow& window);
	friend bool operator==(const Cell& cell1, const Cell& cell2);
};

