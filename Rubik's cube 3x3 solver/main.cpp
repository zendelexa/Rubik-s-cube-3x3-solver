#include "cube.hpp"

int main()
{
	Cube cube;

	cube.makeMove(FaceName::B, 1);
	cube.print();

	return 0;
}