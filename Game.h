#pragma once
#define _USE_MATH_DEFINES
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include<vector>
#include<iostream>
#include<cassert>
#include<queue>

using namespace sf;
using std::vector;

class Game
{
	//Window
	RenderWindow *window_;
	bool active;
	int standard_size_unit_;
	int score_;

	//Fonts
	Font font_;

	vector<vector<int>> tile_values_;
public:
	//functions
	bool IsActive();
	void Draw();
	void Update();
	void ProcessMerge(int, char);
	void ProcessSlide(int, char);
	void KeyboardHandler(Event);
	void GenerateNewTile();
	bool PossiblePlaceForNewTile();
	void ProcessLine(int,char);
	sf::Color GetAppropriateColor(int value);
	//constructor
	Game(RenderWindow* window, unsigned int,int,int);
	~Game();
};

