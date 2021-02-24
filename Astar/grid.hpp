#pragma once
#include <vector>
#include "cell.hpp"
#include "const.hpp"

class Grid
{
private:
	std::vector<std::shared_ptr<Cell>> cells;
	int width, height;
	
	
public:
	bool starting_point_set, end_point_set;
	std::shared_ptr<Cell> getCell(int row, int col);
	std::shared_ptr<Cell> getStartingCell();
	std::shared_ptr<Cell> getEndCell();
	void generateCells(int width, int height);
	void setObstacle(int row, int col);
	void setStart(int row, int col);
	void setEnd(int row, int col);
	void clearCells(std::string whatToClear);
	void clearAlgorithm();
	void clearAll();
	void draw(sf::RenderWindow& window);
	void update();
	Grid& operator=(const Grid& gridToAssign);
	Grid();
};

