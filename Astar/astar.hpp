#pragma once
#include <memory>
#include <list>
#include "cell.hpp"
#include "grid.hpp"

class Astar {
public:
	Astar(Grid grid);
	void findPatch();
	bool path_found;
	int iterations_from_emptying_open_list;
private:
	Grid grid;
	std::list<std::shared_ptr<Cell>> open;
	std::list<std::shared_ptr<Cell>> closed;
	std::shared_ptr<Cell> current_node;
	std::shared_ptr<Cell> destination_node;
	bool reachedDestination();
	void addStartingCellToOpenList();
	void showPath(std::shared_ptr<Cell> node);
	void processNeighbour(std::shared_ptr<Cell> neighbour);
	bool neighbourNotInOpen(std::shared_ptr<Cell> neighbour);
	bool newPathShorter(std::shared_ptr<Cell> neighbour, int distanceBetweanNodes);
	void setNodeCosts(std::shared_ptr<Cell> neighbour, int distanceBetweanNodes);
	bool nodeValid(int row, int col);
	bool rowColValid(int row, int col);
	bool nodeNotInClosed(std::shared_ptr<Cell> node);
};

