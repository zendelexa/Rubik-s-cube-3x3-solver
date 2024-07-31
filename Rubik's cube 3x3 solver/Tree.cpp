#include "Tree.hpp"

#include <memory>

const std::string NO_MOVE = " ";

Tree::Node::Node(const Cube &cube, const std::string &move = NO_MOVE, int blocked_faces = 0, const Node *parent = nullptr)
:
	cube(cube),
	move(move),
	blocked_faces(blocked_faces),
	parent(parent)
{}

Tree::Tree(const Cube &cube)
:
	root(cube)
{
	bfs_order.push(std::make_shared<Tree::Node>(cube));
}

std::vector<std::string> solve(const Cube &start_cube, const Cube &finish_cube)
{
	// unique pointers are used to quickly swap the trees
	std::unique_ptr<Tree> current_tree = std::make_unique<Tree>(start_cube);
	std::unique_ptr<Tree> opposite_tree(std::make_unique<Tree>(finish_cube));

	while (true)
	{
		const std::string FACE_NAMES = "RUFLDB";

		auto current_node = current_tree->bfs_order.front();
		current_tree->bfs_order.pop();

		Cube &cube = current_node->cube;
		current_tree->seen_nodes[cube];
		// TODO
		if (current_tree->seen_nodes.contains(cube));

		
		for (int face_index = 0; face_index < 6; face_index++)
		{

		}
	}

	return std::vector<std::string>();
}
