#include "main_window.hpp"
#include "const.hpp"

MainWindow::MainWindow():selected_col(-1), selected_row(-1), is_setting_start(false), is_setting_end(false), is_searching(false)
{
	this->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Astar", sf::Style::Close | sf::Style::Titlebar);
	grid.generateCells(GRID_WIDTH, GRID_HEIGHT);
	astar = nullptr;
	this->run();
}

void MainWindow::run() {
	while (this->window.isOpen()) {
		handleEvents();
		update();
		draw();
	}
}

void MainWindow::handleEvents()
{
	sf::Event event;
	this->window.pollEvent(event);
	if (event.type == sf::Event::Closed) {
		window.close();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_searching) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
		if (mouseInsideWindow(mousePos)) {
			int col = static_cast<int>(static_cast<float>(mousePos.x) / SCREEN_WIDTH * GRID_WIDTH);
			int row = static_cast<int>(static_cast<float>(mousePos.y) / SCREEN_HEIGHT * GRID_HEIGHT);
			if ((row != selected_row || col != selected_col) && (row>=0 && row<GRID_HEIGHT && col >=0 && col <GRID_WIDTH)) {
				if (is_setting_start) {
					setStart(row, col);
					is_setting_start = false;
				}
				else if (is_setting_end) {
					setEnd(row, col);
					is_setting_end = false;
				}
				else {
					handleClickEvent(row, col);
				}
				selected_row = row;
				selected_col = col;
				
			}
		}
	}
	else if (event.type == sf::Event::KeyPressed && !is_searching) {
		if (event.key.code == sf::Keyboard::S) {
			is_setting_start = !is_setting_start;
		}
		else if (event.key.code == sf::Keyboard::E) {
			is_setting_end = !is_setting_end;
		}
		else if (event.key.code == sf::Keyboard::Space && grid.starting_point_set && grid.end_point_set) {
			grid.clearAlgorithm();
			astar = std::make_shared<Astar>(this->grid);
			is_searching = true;
		}
		else if (event.key.code == sf::Keyboard::C) {
			grid.clearAll();
		}
	}
}

bool MainWindow::mouseInsideWindow(sf::Vector2i mousePos)
{
	return (mousePos.x <= SCREEN_WIDTH && mousePos.y < SCREEN_HEIGHT);
}

void MainWindow::handleClickEvent(int row, int col)
{
	grid.setObstacle(row, col);
}

void MainWindow::setStart(int row, int col)
{
	grid.setStart(row, col);
}

void MainWindow::setEnd(int row, int col)
{
	grid.setEnd(row, col);
}

void MainWindow::update()
{
	if (is_searching) {
		astar->findPatch();
		if (astar->path_found)
		{
			is_searching = false;
		}
	}
	grid.update();
}

void MainWindow::draw() {
	this->window.clear();
	this->grid.draw(window);
	this->window.display();
}