#include "grid.hpp"



std::shared_ptr<Cell> Grid::getCell(int row, int col)
{
	return cells.at(row * this->width + col);
}

std::shared_ptr<Cell> Grid::getStartingCell()
{
	for (std::shared_ptr<Cell> cell : cells) {
		if (cell->is_starting)
		{
			return cell;
		}
	}
}

std::shared_ptr<Cell> Grid::getEndCell()
{
	for (std::shared_ptr<Cell> cell : cells) {
		if (cell->is_end) {
			return cell;
		}
	}
}

Grid::Grid(): width(0), height(0), starting_point_set(false), end_point_set(false)
{
	
}

void Grid::generateCells(int width, int height)
{	
	int cellWidthPixels = SCREEN_WIDTH / width;
	int cellHeightPixels = SCREEN_HEIGHT / height;
	this->width = width;
	this->height = height;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			cells.push_back(std::make_shared<Cell>(sf::Vector2i(col * cellWidthPixels, row * cellHeightPixels), sf::Vector2f(cellWidthPixels, cellHeightPixels), sf::Vector2i(row, col)));
		}
	}
}

void Grid::setObstacle(int row, int col)
{
	getCell(row, col)->is_obstacle = !getCell(row, col)->is_obstacle;
}

void Grid::setStart(int row, int col)
{
	clearCells("Start");
	getCell(row, col)->is_starting = true;
	starting_point_set = true;
}

void Grid::setEnd(int row, int col)
{
	clearCells("End");
	getCell(row, col)->is_end = true;
	end_point_set = true;
}

void Grid::clearCells(std::string whatToClear)
{
	for (std::shared_ptr<Cell> cell : cells) {
		if (whatToClear == "Start" && cell->is_starting) {
			cell->is_starting = false;
			starting_point_set = false;
		}
		else if (whatToClear == "End" && cell->is_end) {
			cell->is_end = false;
			end_point_set = false;
		}
	}
}

void Grid::clearAlgorithm()
{
	for (std::shared_ptr<Cell> cell : cells) {
		cell->is_closed = false;
		cell->is_open = false;
		cell->is_path = false;
	}
}

void Grid::clearAll()
{
	for (std::shared_ptr<Cell> cell : cells) {
		cell->is_closed = false;
		cell->is_open = false;
		cell->is_path = false;
		cell->is_end = false;
		cell->is_starting = false;
		cell->is_obstacle = false;
	}
	starting_point_set = false;
	end_point_set = false;
}

void Grid::draw(sf::RenderWindow& window)
{
	for (std::shared_ptr<Cell> cell : cells) {
		cell->draw(window);
	}
}

void Grid::update()
{
	for (std::shared_ptr<Cell> cell : cells) {
		cell->update();
	}
}

Grid& Grid::operator=(const Grid& gridToAssign)
{
	if (this == &gridToAssign) {
		return *this;
	}
	this->cells = gridToAssign.cells;
	this->height = gridToAssign.height;
	this->width = gridToAssign.width;
	return *this;
}
