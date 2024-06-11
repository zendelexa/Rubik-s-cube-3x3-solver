#pragma once

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

const int SIDE_LENGTH = 3;

enum FaceName { R, U, F, L, D, B };
using Face = std::vector<std::vector<char>>;
using StickerCoords = std::tuple<FaceName, int, int>;
using Cycle = std::vector<StickerCoords>;
using Move = std::vector<Cycle>;

class Cube
{
	std::vector<Face> faces { 6, Face(SIDE_LENGTH, std::vector<char>(SIDE_LENGTH)) };
	
	static const std::string COLORS;

	static const std::vector<Move> MOVE_TABLE;

public:
	Cube(); // Solved cube

	char &operator[](const StickerCoords &sticker_coords);

	void makeMove(FaceName face_name, int reps);

	void print() const;

	
};

