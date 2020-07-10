#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	int scorecounter = 0;
	int xAxis = 70, yAxis = 10, d1 = 3, d2 = 3, downpadding = 5, sidepadding = 20, counter = 0;
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	bool CheckForObstacle(const Location& loc) const;
	void SpawnObstacle(std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	void DrawBorder();
	void DrawObstacles();
	void DrawScore();
	void OneDigitScore( int remainder );
	void print0();
	void print1();
	void print2();
	void print3();
	void print4();
	void print5();
	void print6();
	void print7();
	void print8();
	void print9();
private:
	static constexpr Color borderColor = Colors::Yellow;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color scoreColor = Colors::Cyan;
	static constexpr int dimension = 20;
	static constexpr int cellPadding = 1;
	static constexpr int width = 32;
	static constexpr int height = 24;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;
	bool hasObstacle[width * height] = { false };
	Graphics& gfx;
};