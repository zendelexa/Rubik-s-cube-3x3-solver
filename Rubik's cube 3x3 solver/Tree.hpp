#include "cube.hpp"

#include <queue>
#include <unordered_map>

const int BLOCK_R = 1 << 1;
const int BLOCK_U = 1 << 2;
const int BLOCK_F = 1 << 3;
const int BLOCK_L = 1 << 4;
const int BLOCK_D = 1 << 5;
const int BLOCK_B = 1 << 6;

const std::vector<int> BLOCK_SIDE = { BLOCK_R, BLOCK_U, BLOCK_F, BLOCK_L, BLOCK_D, BLOCK_B };

class Tree
{
	struct TreeNode
	{
		Cube cube;
		std::string move;
		int blocked_faces;

		const TreeNode *parent;

		TreeNode(const Cube &cube, const std::string &move, int blocked_faces, const TreeNode *parent); // Does not perform the move
	};

	TreeNode root;
	std::queue<TreeNode*> bfs_order;
	std::unordered_map<std::string, TreeNode*> seen_nodes;

public:
	Tree(const Cube &cube);
};