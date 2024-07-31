#include "cube.hpp"

#include <queue>
#include <unordered_map>
#include <memory>

const int BLOCK_R = 1 << 1;
const int BLOCK_U = 1 << 2;
const int BLOCK_F = 1 << 3;
const int BLOCK_L = 1 << 4;
const int BLOCK_D = 1 << 5;
const int BLOCK_B = 1 << 6;

const std::vector<int> BLOCK_SIDE = { BLOCK_R, BLOCK_U, BLOCK_F, BLOCK_L, BLOCK_D, BLOCK_B };

class Tree
{
	struct Node
	{
		Cube cube;
		std::string move;
		int blocked_faces;

		const Node *parent;

		Node(const Cube &cube, const std::string &move, int blocked_faces, const Node *parent); // Does not perform the move
	};

	Node root;
	std::queue<std::shared_ptr<Node>> bfs_order;
	std::unordered_map<Cube, std::shared_ptr<Node>> seen_nodes;

public:
	Tree(const Cube &cube);

	friend std::vector<std::string> solve(const Cube &start_cube, const Cube &finish_cube);
};