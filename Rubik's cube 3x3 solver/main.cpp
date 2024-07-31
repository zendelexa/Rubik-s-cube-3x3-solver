#include "cube.hpp"
#include "Tree.hpp"

#include <iostream>

int main()
{
	Cube cube;

	/*cube.makeMove(FaceName::R, 1);
	cube.makeMove(FaceName::U, 1);
	cube.makeMove(FaceName::R, 3);
	cube.makeMove(FaceName::U, 3);*/
	cube.makeMove(FaceName::R, 1);
	cube.makeMove(FaceName::F, 1);
	cube.makeMove(FaceName::U, 3);
	cube.makeMove(FaceName::F, 1);
	cube.makeMove(FaceName::B, 3);
	cube.makeMove(FaceName::D, 1);
	/*cube.makeMove(FaceName::B, 1);
	cube.makeMove(FaceName::U, 1);
	cube.makeMove(FaceName::R, 2);
	cube.makeMove(FaceName::D, 1);*/
	/*cube.makeMove(FaceName::L, 3);
	cube.makeMove(FaceName::D, 2);
	cube.makeMove(FaceName::R, 1);
	cube.makeMove(FaceName::D, 2);
	cube.makeMove(FaceName::F, 2);
	cube.makeMove(FaceName::D, 2);
	cube.makeMove(FaceName::R, 3);
	cube.makeMove(FaceName::F, 2);
	cube.makeMove(FaceName::D, 2);
	cube.makeMove(FaceName::R, 3);
	cube.makeMove(FaceName::L, 3);*/
	cube.print();

	auto moves = solve(cube, Cube());
	for (auto move : moves)
		std::cout << move << " ";

	return 0;
}