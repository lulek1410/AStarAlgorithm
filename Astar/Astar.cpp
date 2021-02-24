
#include "astar.hpp"

Astar::Astar(Grid grid): path_found(false), iterations_from_emptying_open_list(0)
{
	this->grid = grid;
	this->destination_node = this->grid.getEndCell();
	addStartingCellToOpenList();
}

bool Astar::reachedDestination()
{
	return current_node == destination_node;
}

void Astar::addStartingCellToOpenList()
{
	open.push_back(grid.getStartingCell());
}

void Astar::showPath(std::shared_ptr<Cell> node)
{
	if (node->is_starting) {
		return;
	}
	node->is_path = true;
	showPath(node->parrent);
}

void Astar::findPatch()
{
	if (!path_found) {
		if (open.empty()) {
			path_found = true;
			return;
		}
		open.sort([](const std::shared_ptr<Cell>& cell1, const std::shared_ptr<Cell>& cell2) {
			return cell1->f < cell2->f;
			});
		this->current_node = open.front();
		current_node->is_closed = true;
		closed.push_back(open.front());
		open.pop_front();
		if (iterations_from_emptying_open_list > 2) {
			path_found = true;
			return;
		}
		if (this->current_node == this->destination_node)
		{
			showPath(destination_node);
			path_found = true;
			return;
		}
		for (int r = -1; r < 2; r++) {
			for (int c = -1; c < 2; c++) {
				if (!(r == 0 && c == 0)) {
					if (nodeValid(current_node->row + r, current_node->col + c)) {
						processNeighbour(grid.getCell(current_node->row + r, current_node->col + c));
					}
				}
			}
		}
	}
}

void Astar::processNeighbour(std::shared_ptr<Cell> neighbour)
{
	int distanceBetweanNodes = static_cast<int>(10 * sqrt(pow(current_node->col - neighbour->col, 2.0)
		+ pow(current_node->row - neighbour->row, 2.0)));
	if (newPathShorter(neighbour, distanceBetweanNodes) || neighbourNotInOpen(neighbour)) {
		setNodeCosts(neighbour, distanceBetweanNodes);
		neighbour->parrent = current_node;
		if (neighbourNotInOpen(neighbour)) {
			open.push_back(neighbour);
			neighbour->is_open = true;
		}
	}
}

bool Astar::neighbourNotInOpen(std::shared_ptr<Cell> neighbour)
{
	for (std::shared_ptr<Cell> cell : open) {
		if (cell == neighbour) {
			return false;
		}
	}
	return true;
}

bool Astar::newPathShorter(std::shared_ptr<Cell> neighbour, int distanceBetweanNodes)
{
	if (neighbour->f > current_node->f + distanceBetweanNodes) {
		return true;
	}
	return false;
}

void Astar::setNodeCosts(std::shared_ptr<Cell> neighbour, int distanceBetweanNodes)
{
	neighbour->g = current_node->g + distanceBetweanNodes;
	neighbour->h = static_cast<int>(10 * sqrt(pow(neighbour->col - destination_node->col, 2.0)
					+ pow(neighbour->row - destination_node->row, 2.0)));
	neighbour->f = neighbour->g + neighbour->h;
}

bool Astar::nodeValid(int row, int col)
{
	if (rowColValid(row, col)) {
		if (!grid.getCell(row, col)->is_obstacle && nodeNotInClosed(grid.getCell(row, col))) {
			return true;
		}
	}
	return false;
}

bool Astar::rowColValid(int row, int col)
{
	return (row > -1 && row < GRID_WIDTH&& col > -1 && col < GRID_HEIGHT);
}

bool Astar::nodeNotInClosed(std::shared_ptr<Cell> node)
{
	for (std::shared_ptr<Cell> cell : closed) {
		if (cell == node) {
			return false;
		}
	}
	return true;
}


