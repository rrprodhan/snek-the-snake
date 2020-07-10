#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c)
{
	/*assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);*/

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * dimension + off_x + cellPadding, loc.y * dimension+ off_y + cellPadding, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

bool Board::CheckForObstacle(const Location & loc) const
{
	return hasObstacle[loc.y * width + loc.x];
}

void Board::SpawnObstacle(std::mt19937 & rng, const Snake & snake, const Goal& goal)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || CheckForObstacle(newLoc) || goal.GetLocation() == newLoc);

	hasObstacle[newLoc.y * width + newLoc.x] = true;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top - 48 + (borderWidth + borderPadding) * 10 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	// top
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);										// Line(68 - 74) This part is the measurement of the area inside the border
	// left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);		// where the snake can move freely. :) 
	// right
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);		//
	// bottom
	gfx.DrawRect(left, bottom - borderWidth, right , bottom , borderColor);								//
}

void Board::DrawObstacles()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (CheckForObstacle({ x,y }))
			{
				DrawCell({ x,y }, obstacleColor);
			}
		}
	}
}

void Board::DrawScore()
{
	// S print

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 10, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + 10, yAxis + 10 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 20, d1, d2, scoreColor);
	}

	// C print

	xAxis += sidepadding;

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 5; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 20, d1, d2, scoreColor);
	}

	// O print

	xAxis += sidepadding;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 4; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	xAxis += 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 21, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 4; counter++)
	{
		gfx.DrawRectDim(xAxis + 8, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	// R print

	xAxis += sidepadding;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 1 + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 4; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis  + (counter * downpadding), d1, d2, scoreColor);
	}

	xAxis += 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 11, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 8, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 14 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 9 + 1, yAxis + 14 + (counter * downpadding), d1, d2, scoreColor);
	}

	// E print

	xAxis += sidepadding;

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 5; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 20, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 10, d1, d2, scoreColor);
	}

	// : print

	xAxis += sidepadding;

	gfx.DrawRectDim(xAxis + 3, yAxis + 3, d1, d2, scoreColor);
	gfx.DrawRectDim(xAxis + 3, yAxis + 15, d1, d2, scoreColor);
	

	if (scorecounter == 0)
	{
		print0();
	}

	if (scorecounter >= 1 && scorecounter <= 1000)
	{
		int duplicate_score, reversed_number = 0, remainder = 0, position = 0;

		duplicate_score = scorecounter;

		while (scorecounter != 0)
		{
			remainder = scorecounter % 10;

			reversed_number = reversed_number + ((position * 10) + remainder);

			position++;

			scorecounter /= 10;
		}

		while (reversed_number != 0)
		{
			remainder = reversed_number % 10;

			OneDigitScore(remainder);

			reversed_number /= 10;
		}


		scorecounter = duplicate_score;
	}

	xAxis = 70, yAxis = 10, d1 = 3, d2 = 3, downpadding = 5, sidepadding = 20, counter = 0;
	

}

void Board::OneDigitScore( int remainder )
{
	
		if (remainder == 0)
			print0();

		if (remainder == 1)
			print1();

		if (remainder == 2)
			print2();

		if (remainder == 3)
			print3();

		if (remainder == 4)
			print4();

		if (remainder == 5)
			print5();

		if (remainder == 6)
			print6();

		if (remainder == 7)
			print7();

		if (remainder == 8)
			print8();

		if (remainder == 9)
			print9();
		
}


void Board::print0()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 4; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	xAxis += 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 21, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 4; counter++)
	{
		gfx.DrawRectDim(xAxis + 8, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

}

void Board::print1()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 5; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

}

void Board::print2()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 11, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 9, yAxis + 7 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 7, yAxis + 11 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 5, yAxis + 15 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 3, yAxis + 19 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + 1 + (counter * downpadding), yAxis + 23, d1, d2, scoreColor);
	}

}

void Board::print3()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 1 + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	xAxis += 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + (counter * downpadding), yAxis + 21, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 4; counter++)
	{
		gfx.DrawRectDim(xAxis + 7, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + (counter * downpadding), yAxis + 10.5, d1, d2, scoreColor);
	}
}

void Board::print4()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 7, yAxis -11 + 11 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 5, yAxis -11 + 15 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 3, yAxis -11 + 19 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + 1 + (counter * downpadding), yAxis -11 + 23, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 5; counter++)
	{
		gfx.DrawRectDim(xAxis + 15, yAxis - 11 + 11 + (counter * downpadding), d1, d2, scoreColor);
	}

}

void Board::print5()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 10, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 10 + 10, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis + 10, yAxis + 10 + 5 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}
}

void Board::print6()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 5; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 20, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 10, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + 10, yAxis + 10 + (counter * downpadding), d1, d2, scoreColor);
	}
}

void Board::print7()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + 11, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + 9, yAxis + 7 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + 7, yAxis + 11 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + 5, yAxis + 15 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis - 2 + 3, yAxis + 19 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}
}

void Board::print8()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	xAxis += 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 11, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 7, yAxis + 3 + (counter * downpadding), d1, d2, scoreColor);
	}

	xAxis -= 3;

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 14 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 9, yAxis + 14 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 2; counter++)
	{
		gfx.DrawRectDim(xAxis + 2 + (counter * downpadding), yAxis + 22, d1, d2, scoreColor);
	}
}

void Board::print9()
{
	xAxis += sidepadding;

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 5; counter++)
	{
		gfx.DrawRectDim(xAxis + 10, yAxis + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 20, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + (counter * downpadding), yAxis + 10, d1, d2, scoreColor);
	}

	for (counter = 0; counter < 3; counter++)
	{
		gfx.DrawRectDim(xAxis + 10, yAxis + 10 + (counter * downpadding), d1, d2, scoreColor);
	}

	for (counter = 0; counter < 1; counter++)
	{
		gfx.DrawRectDim(xAxis, yAxis + 5 + (counter * downpadding), d1, d2, scoreColor);
	}
}