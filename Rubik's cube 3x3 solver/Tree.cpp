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
	const std::string FACE_NAMES[6] = { "R", "U", "F", "L", "D", "B" };
	const std::string TURN_AMOUNTS[3] = { "", "2", "'" };

	// unique pointers are used to quickly swap the trees
	std::unique_ptr<Tree> current_tree = std::make_unique<Tree>(start_cube);
	std::unique_ptr<Tree> opposite_tree = std::make_unique<Tree>(finish_cube);
	bool is_current_tree_start_tree = true;

	while (true)
	{
		std::swap(current_tree, opposite_tree);
		is_current_tree_start_tree = !is_current_tree_start_tree;

		auto current_node = current_tree->bfs_order.front();
		current_tree->bfs_order.pop();

		Cube &cube = current_node->cube;
		if (current_tree->seen_nodes.contains(cube))
			continue;
		current_tree->seen_nodes[cube] = current_node;
		
		if (opposite_tree->seen_nodes.contains(cube))
		{
			std::vector<std::string> current_moves;
			for (const Tree::Node *tmp_node = current_node.get(); tmp_node->move != NO_MOVE; tmp_node = tmp_node->parent)
			{
				current_moves.push_back(tmp_node->move);
			}

			std::vector<std::string> opposite_moves;
			for (const Tree::Node *tmp_node = opposite_tree->seen_nodes[current_node->cube].get(); tmp_node->move != NO_MOVE; tmp_node = tmp_node->parent)
			{
				opposite_moves.push_back(tmp_node->move);
			}

			if (!is_current_tree_start_tree)
				std::swap(current_moves, opposite_moves);

			auto reverseMove = [](const std::string &move)
				{
					char last_char = move[move.size() - 1];
					if (last_char == '2') return move;
					if (last_char == '\'') return std::string(1, move[0]);
					return std::string(1, move[0]) + '\'';
				};
			for (std::string &move : opposite_moves)
				move = reverseMove(move);
			std::reverse(current_moves.begin(), current_moves.end());
			
			for (std::string &move : opposite_moves)
				current_moves.push_back(move);
			return current_moves; // Exit here!
		}
		
		for (int face_index = 0; face_index < 6; face_index++)
		{
			bool is_current_side_blocked = (current_node->blocked_faces & BLOCK_FACE[face_index]) != 0;
			if (is_current_side_blocked) continue;

			int new_blocked_faces = BLOCK_FACE[face_index];
			bool is_opposite_face_blocked = (current_node->blocked_faces << 3) == new_blocked_faces || 
											current_node->blocked_faces == (new_blocked_faces << 3);
			if (is_opposite_face_blocked)
				new_blocked_faces = new_blocked_faces | current_node->blocked_faces;

			Cube new_cube = cube;
			for (int rotations_performed = 1; rotations_performed < 4; rotations_performed++)
			{
				new_cube.makeMove((FaceName)(face_index), 1);
				std::string new_move = FACE_NAMES[face_index] + TURN_AMOUNTS[rotations_performed - 1];
				if (!current_tree->seen_nodes.contains(new_cube))
				{
					current_tree->bfs_order.push(std::make_shared<Tree::Node>(new_cube, new_move, new_blocked_faces, current_node.get()));
				}
			}
		}
	}

	return std::vector<std::string>();
}
