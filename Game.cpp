#include "Game.h"

Game::Game(RenderWindow * window, unsigned int standard_size_unit,int first_x,int first_y) : window_(window),standard_size_unit_(standard_size_unit)
{
	this->tile_values_ = vector < vector<int>>(4, vector<int>(4, 0));
	this->window_->setFramerateLimit(60);
	this->tile_values_[first_x][first_y] = 2;
	if (!this->font_.loadFromFile("Fonts\\ClearSans-Bold.ttf")) {
		std::cout << "Failed to load ClearSans font";
	}
	this->active = true;
}


Game::~Game() {

}

bool Game::IsActive()
{
	return this->active;
}

void Game::Draw() {
	window_->clear(Color(187,173,160,0));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			RectangleShape rectangle(Vector2f(7 * standard_size_unit_, 7 * standard_size_unit_));
			rectangle.setFillColor(GetAppropriateColor(tile_values_[i][j]));
			rectangle.setPosition((i+1 + i*7)*standard_size_unit_, (j+1 + j * 7)*standard_size_unit_);
			window_->draw(rectangle);
			if (!tile_values_[i][j]) continue; // if value is 0 dont draw a value
			Text text;
			text.setFont(font_); // font is a sf::Font
			text.setString(std::to_string(tile_values_[i][j]));
			text.setCharacterSize(3.5*standard_size_unit_); // in pixels, not points!
			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.width / 2, textRect.height / 2);
			text.setPosition((i + 1 + i * 7 + 3.2)*standard_size_unit_, (j + 1 + j * 7+2.5)*standard_size_unit_);
			if (tile_values_[i][j] == 2 or tile_values_[i][j] == 4) {
				text.setFillColor(Color(119, 110, 101, 255));
			} else {
				text.setFillColor(Color(249, 246, 242, 255));
			}
			window_->draw(text);
		}
	}
	window_->display();
}

void Game::ProcessMerge(int i, char dir)
{
	assert(dir == 'W' or dir == 'S' or dir == 'A' or dir == 'D');
	assert(i >= 0 and i <= 3);
	if (dir == 'W') {
		if (tile_values_[i][0] == tile_values_[i][1]) {
			tile_values_[i][0] *= 2;
			tile_values_[i][1] = 0;
		}
		if (tile_values_[i][1] == tile_values_[i][2]) {
			tile_values_[i][1] *= 2;
			tile_values_[i][2] = 0;
		}
		if (tile_values_[i][2] == tile_values_[i][3]) {
			tile_values_[i][2] *= 2;
			tile_values_[i][3] = 0;
		}
		//ProcessColumn(i, 'W');
	}
	else if (dir == 'S') {
		if (tile_values_[i][3] == tile_values_[i][2]) {
			tile_values_[i][3] *= 2;
			tile_values_[i][2] = 0;
		}
		if (tile_values_[i][2] == tile_values_[i][1]) {
			tile_values_[i][2] *= 2;
			tile_values_[i][1] = 0;
		}
		if (tile_values_[i][1] == tile_values_[i][0]) {
			tile_values_[i][1] *= 2;
			tile_values_[i][0] = 0;
		}
		//ProcessColumn(i, 'S');
	}
	else if (dir == 'A') {
		if (tile_values_[0][i] == tile_values_[1][i]) {
			tile_values_[0][i] *= 2;
			tile_values_[1][i] = 0;
		}
		if (tile_values_[1][i] == tile_values_[2][i]) {
			tile_values_[1][i] *= 2;
			tile_values_[2][i] = 0;
		}
		if (tile_values_[2][i] == tile_values_[3][i]) {
			tile_values_[2][i] *= 2;
			tile_values_[3][i] = 0;
		}
		//ProcessRow(i, 'A');
	}
	else if (dir == 'D') {
		if (tile_values_[3][i] == tile_values_[2][i]) {
			tile_values_[3][i] *= 2;
			tile_values_[2][i] = 0;
		}
		if (tile_values_[2][i] == tile_values_[1][i]) {
			tile_values_[2][i] *= 2;
			tile_values_[1][i] = 0;
		}
		if (tile_values_[1][i] == tile_values_[0][i]) {
			tile_values_[1][i] *= 2;
			tile_values_[0][i] = 0;
		}
		//ProcessRow(i, 'D');
	}
}
//TODO Merge ProcessColumn and ProcessRow
void Game::ProcessSlide(int i, char dir)
{
	std::queue<int> free_tile;
	assert(dir == 'W' or dir == 'S' or dir == 'A' or dir == 'D');
	if (dir == 'W') {
		for (int j = 0; j < 4; j++) {
			if (tile_values_[i][j] == 0) {
				free_tile.push(j);
			}
			else if (tile_values_[i][j] and free_tile.size()){
				tile_values_[i][free_tile.front()] = tile_values_[i][j];
				tile_values_[i][j] = 0;
				free_tile.pop();
				free_tile.push(j); // since its making new free spot
			}
		}		
	}
	else if (dir == 'S'){
		for (int j = 3; j >= 0; j--) {
			if (tile_values_[i][j] == 0) {
				free_tile.push(j);
			}
			else if (tile_values_[i][j] and free_tile.size()) {
				tile_values_[i][free_tile.front()] = tile_values_[i][j];
				tile_values_[i][j] = 0;
				free_tile.pop();
				free_tile.push(j); // since its making new free spot
			}
		}
	}
	else if (dir == 'A') {
		for (int j = 0; j < 4; j++) {
			if (tile_values_[j][i] == 0) {
				free_tile.push(j);
			}
			else if (tile_values_[j][i] and free_tile.size()) {
				tile_values_[free_tile.front()][i] = tile_values_[j][i];
				tile_values_[j][i] = 0;
				free_tile.pop();
				free_tile.push(j); // since its making new free spot
			}
		}
	}
	else if (dir=='D'){
		for (int j = 3; j >= 0; j--) {
			if (tile_values_[j][i] == 0) {
				free_tile.push(j);
			}
			else if (tile_values_[j][i] and free_tile.size()) {
				tile_values_[free_tile.front()][i] = tile_values_[j][i];
				tile_values_[j][i] = 0;
				free_tile.pop();
				free_tile.push(j); // since its making new free spot
			}
		}
	}
}

void Game::ProcessLine(int i, char dir) {
	
	ProcessSlide(i, dir);
	ProcessMerge(i, dir);
	ProcessSlide(i, dir);
	
}

void Game::KeyboardHandler(Event event)
{
	vector < vector<int>> copy = tile_values_;
	for (int i = 0; i < 4; i++) {
		if (event.key.code == Keyboard::Down or event.key.code == Keyboard::S) {
			ProcessLine(i, 'S');
		}
		else if (event.key.code == Keyboard::Up or event.key.code == Keyboard::W) {
			ProcessLine(i, 'W');
		}
		else if (event.key.code == Keyboard::Right or event.key.code == Keyboard::D) {
			ProcessLine(i, 'D');
		}
		else if (event.key.code == Keyboard::Left or event.key.code == Keyboard::A) {
			ProcessLine(i, 'A');
		}
	}
	if (tile_values_ != copy) {
		GenerateNewTile();
	}
}

void Game::GenerateNewTile()
{
	if (not PossiblePlaceForNewTile()) {
		active = false;
		return;
	}
	int new_x, new_y;
	do {
		new_x = rand() % 4;
		new_y = rand() % 4;
	} while (tile_values_[new_x][new_y] != 0);
	tile_values_[new_x][new_y] = 2 + rand() % 2 * 2;
}

bool Game::PossiblePlaceForNewTile()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!tile_values_[i][j]) return true;
		}
	}
	return false;
}

sf::Color Game::GetAppropriateColor(int value) {
	switch (value) {
	case 0: return Color(238, 228, 218, 90);
	case 2: return Color(250, 248, 239, 255);
	case 4: return Color(237, 224, 200, 255);
	case 8: return Color(242, 177, 121, 255);
	case 16: return Color(245, 149, 99, 255);
	case 32: return Color(246, 124, 95, 255);
	case 64: return Color(246, 94, 59, 255);
	case 128: return Color(237, 207, 114, 255);
	case 256: return Color(237, 204, 97, 255);
	case 512: return Color(255, 255, 0, 90);
	case 1024: return Color(255, 255, 0, 90);
	case 2048: return Color(255, 255, 0, 90);
	case 4096: return Color(255, 255, 0, 90);
	default: return Color(0, 0, 0, 255);
	}
}