#include "cell.hpp"

Cell::Cell(sf::Vector2i position, sf::Vector2f size, sf::Vector2i rowcol) : is_obstacle(false), is_starting(false), is_end(false), is_closed(false), is_open(false), is_path(false)
{
	this->rect.setPosition(position.x, position.y);
	this->rect.setSize(size);
	this->rect.setFillColor(sf::Color::White);
	this->rect.setOutlineThickness(2);
	this->rect.setOutlineColor(sf::Color::Yellow);
	this->row = rowcol.x;
	this->col = rowcol.y;
	this->f = 0;
	this->g = 0;
	this->h = 0;
}

void Cell::update()
{
	if (this->is_obstacle) {
		this->rect.setFillColor(sf::Color::Black);
	}
	else if (this->is_starting) {
		this->rect.setFillColor(sf::Color::Blue);
	}
	else if (this->is_end) {
		this->rect.setFillColor(sf::Color::Magenta);
	}
	else if (this->is_path) {
		this->rect.setFillColor(sf::Color::Yellow);
	}
	else if (this->is_closed) {
		this->rect.setFillColor(sf::Color::Red);
	}
	else if (this->is_open) {
		this->rect.setFillColor(sf::Color::Green);
	}
	else {
		this->rect.setFillColor(sf::Color::White);
	}
}

void Cell::draw(sf::RenderWindow& window)
{
	update();
	window.draw(this->rect);
}

bool operator==(const Cell& cell1, const Cell& cell2)
{
	return (cell1.row == cell2.row && cell1.col == cell2.col);
}
