#include "cube.hpp"

#include <iostream>

Cube::Cube()
{
	for (int face_index = 0; face_index < 6; face_index++)
		for (std::vector<char> &v : faces[face_index])
			std::fill(v.begin(), v.end(), COLORS[face_index]);
}

const char &Cube::operator[](const StickerCoords &sticker_coords) const
{
	const auto &[face_name, row, col] = sticker_coords;
	return faces[face_name][row][col];
}

char &Cube::operator[](const StickerCoords &sticker_coords)
{
	const auto &[face_name, row, col] = sticker_coords;
	return faces[face_name][row][col];
}

void Cube::makeMove(FaceName face_name, int reps)
{
	const Move &move = MOVE_TABLE[face_name];
	for (const Cycle &cycle : move)
	{
		for (int rep = 0; rep < reps; rep++)
		{
			char start_sticker = (*this)[cycle[3]];
			for (int i = 2; i >= 0; i--)
				(*this)[cycle[i + 1]] = (*this)[cycle[i]];
			(*this)[cycle[0]] = start_sticker;
		}
	}
}

void Cube::print() const
{
	for (const Face &face : faces)
	{
		for (const std::vector<char> &row : face)
		{
			for (char sticker : row) std::cout << sticker;
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}

std::string Cube::stringify() const
{
	std::string res;
	res.resize(6 * SIDE_LENGTH * SIDE_LENGTH);
	int i = 0;
	for (const Face &face : faces)
		for (const std::vector<char> &row : face)
			for (char sticker : row)
				res[i++] = sticker;
	return res;
}

bool Cube::operator==(const Cube &other) const
{
	for (int face_index = 0; face_index < 6; face_index++)
		for (int row_index = 0; row_index < SIDE_LENGTH; row_index++)
			for (int col_index = 0; col_index < SIDE_LENGTH; col_index++)
			{
				StickerCoords sticker_coords{(FaceName)face_index, row_index, col_index};
				if ((*this)[sticker_coords] != other[sticker_coords]) return false;
			}
	return true;
}

const std::string Cube::COLORS = "RWGOYB";
const std::vector<Move> Cube::MOVE_TABLE
{
	{ // R move
		Cycle
		{
			{ FaceName::F, 0, 2 },
			{ FaceName::U, 0, 2 },
			{ FaceName::B, 2, 0 },
			{ FaceName::D, 0, 2 }
		},
		Cycle
		{
			{ FaceName::F, 1, 2 },
			{ FaceName::U, 1, 2 },
			{ FaceName::B, 1, 0 },
			{ FaceName::D, 1, 2 }
		},
		Cycle
		{
			{ FaceName::F, 2, 2 },
			{ FaceName::U, 2, 2 },
			{ FaceName::B, 0, 0 },
			{ FaceName::D, 2, 2 }
		},

		Cycle
		{
			{ FaceName::R, 0, 0 },
			{ FaceName::R, 0, 2 },
			{ FaceName::R, 2, 2 },
			{ FaceName::R, 2, 0 }
		},
		Cycle
		{
			{ FaceName::R, 0, 1 },
			{ FaceName::R, 1, 2 },
			{ FaceName::R, 2, 1 },
			{ FaceName::R, 1, 0 }
		}
	},

	{ // U move
		Cycle
		{
			{ FaceName::R, 0, 0 },
			{ FaceName::F, 0, 0 },
			{ FaceName::L, 0, 0 },
			{ FaceName::B, 0, 0 }

		},
		Cycle
		{
			{ FaceName::R, 0, 1 },
			{ FaceName::F, 0, 1 },
			{ FaceName::L, 0, 1 },
			{ FaceName::B, 0, 1 }
		},
		Cycle
		{
			{ FaceName::R, 0, 2 },
			{ FaceName::F, 0, 2 },
			{ FaceName::L, 0, 2 },
			{ FaceName::B, 0, 2 }
		},

		Cycle
		{
			{ FaceName::U, 0, 0 },
			{ FaceName::U, 0, 2 },
			{ FaceName::U, 2, 2 },
			{ FaceName::U, 2, 0 }
		},
		Cycle
		{
			{ FaceName::U, 0, 1 },
			{ FaceName::U, 1, 2 },
			{ FaceName::U, 2, 1 },
			{ FaceName::U, 1, 0 }
		}
	},

	{ // F move
		Cycle
		{
			{ FaceName::U, 2, 0 },
			{ FaceName::R, 0, 0 },
			{ FaceName::D, 0, 2 },
			{ FaceName::L, 2, 2 }

		},
		Cycle
		{
			{ FaceName::U, 2, 1 },
			{ FaceName::R, 1, 0 },
			{ FaceName::D, 0, 1 },
			{ FaceName::L, 1, 2 }
		},
		Cycle
		{
			{ FaceName::U, 2, 2 },
			{ FaceName::R, 2, 0 },
			{ FaceName::D, 0, 0 },
			{ FaceName::L, 0, 2 }
		},

		Cycle
		{
			{ FaceName::F, 0, 0 },
			{ FaceName::F, 0, 2 },
			{ FaceName::F, 2, 2 },
			{ FaceName::F, 2, 0 }
		},
		Cycle
		{
			{ FaceName::F, 0, 1 },
			{ FaceName::F, 1, 2 },
			{ FaceName::F, 2, 1 },
			{ FaceName::F, 1, 0 }
		}
	},

	{ // L move
		Cycle
		{
			{ FaceName::F, 0, 0 },
			{ FaceName::D, 0, 0 },
			{ FaceName::B, 2, 2 },
			{ FaceName::U, 0, 0 }
		},
		Cycle
		{
			{ FaceName::F, 1, 0 },
			{ FaceName::D, 1, 0 },
			{ FaceName::B, 1, 2 },
			{ FaceName::U, 1, 0 }
		},
		Cycle
		{
			{ FaceName::F, 2, 0 },
			{ FaceName::D, 2, 0 },
			{ FaceName::B, 0, 2 },
			{ FaceName::U, 2, 0 }
		},

		Cycle
		{
			{ FaceName::L, 0, 0 },
			{ FaceName::L, 0, 2 },
			{ FaceName::L, 2, 2 },
			{ FaceName::L, 2, 0 }
		},
		Cycle
		{
			{ FaceName::L, 0, 1 },
			{ FaceName::L, 1, 2 },
			{ FaceName::L, 2, 1 },
			{ FaceName::L, 1, 0 }
		}
	},

	{ // D move
		Cycle
		{
			{ FaceName::R, 2, 0 },
			{ FaceName::B, 2, 0 },
			{ FaceName::L, 2, 0 },
			{ FaceName::F, 2, 0 }

		},
		Cycle
		{
			{ FaceName::R, 2, 1 },
			{ FaceName::B, 2, 1 },
			{ FaceName::L, 2, 1 },
			{ FaceName::F, 2, 1 }
		},
		Cycle
		{
			{ FaceName::R, 2, 2 },
			{ FaceName::B, 2, 2 },
			{ FaceName::L, 2, 2 },
			{ FaceName::F, 2, 2 }
		},

		Cycle
		{
			{ FaceName::D, 0, 0 },
			{ FaceName::D, 0, 2 },
			{ FaceName::D, 2, 2 },
			{ FaceName::D, 2, 0 }
		},
		Cycle
		{
			{ FaceName::D, 0, 1 },
			{ FaceName::D, 1, 2 },
			{ FaceName::D, 2, 1 },
			{ FaceName::D, 1, 0 }
		}
	},

	{ // B move
		Cycle
		{
			{ FaceName::U, 0, 0 },
			{ FaceName::L, 2, 0 },
			{ FaceName::D, 2, 2 },
			{ FaceName::R, 0, 2 }

		},
		Cycle
		{
			{ FaceName::U, 0, 1 },
			{ FaceName::L, 1, 0 },
			{ FaceName::D, 2, 1 },
			{ FaceName::R, 1, 2 }
		},
		Cycle
		{
			{ FaceName::U, 0, 2 },
			{ FaceName::L, 0, 0 },
			{ FaceName::D, 2, 0 },
			{ FaceName::R, 2, 2 }
		},

		Cycle
		{
			{ FaceName::B, 0, 0 },
			{ FaceName::B, 0, 2 },
			{ FaceName::B, 2, 2 },
			{ FaceName::B, 2, 0 }
		},
		Cycle
		{
			{ FaceName::B, 0, 1 },
			{ FaceName::B, 1, 2 },
			{ FaceName::B, 2, 1 },
			{ FaceName::B, 1, 0 }
		}
	}
};