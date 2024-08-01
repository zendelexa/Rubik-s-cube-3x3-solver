#include "tree.hpp"

#include <memory>

const std::string NO_MOVE = " ";
const std::string FACE_NAMES[6] = { "R", "U", "F", "L", "D", "B" };
const std::string TURN_AMOUNTS[3] = { "", "2", "'" };

Tree::Node::Node(const Cube &cube, const std::string &move = NO_MOVE, int blocked_faces = 0, const Node *parent = nullptr)
:
	cube(cube),
	move(move),
	blocked_faces(blocked_faces),
	parent(parent)
{}

std::vector<std::string> Tree::Node::getMoveSequence()
{
	std::vector<std::string> res;
	for (const Tree::Node *node = this; node->move != NO_MOVE; node = node->parent)
		res.push_back(node->move);
	reverse(res.begin(), res.end());
	return res;
}

std::optional<Cube> Tree::attemptReaching(const Tree &opposite_tree)
{
	auto current_node = bfs_order.front();
	bfs_order.pop();

	Cube &cube = current_node->cube;
	for (int face_index = 0; face_index < 6; face_index++)
	{
		bool is_current_side_blocked = (current_node->blocked_faces & BLOCK_FACE[face_index]) != 0;
		if (is_current_side_blocked) continue;

		int new_blocked_faces = BLOCK_FACE[face_index];
		bool is_opposite_face_blocked = (current_node->blocked_faces << 3) == new_blocked_faces			  ||
										(new_blocked_faces           << 3) == current_node->blocked_faces;
		if (is_opposite_face_blocked)
			new_blocked_faces = new_blocked_faces | current_node->blocked_faces;

		Cube new_cube = cube;
		for (int turns_performed = 1; turns_performed < 4; turns_performed++)
		{
			new_cube.makeMove((FaceName)(face_index), 1);
			if (seen_nodes.contains(new_cube)) continue;

			std::string new_move = FACE_NAMES[face_index] + TURN_AMOUNTS[turns_performed - 1];
			Tree::Node *new_node = new Tree::Node(new_cube, new_move, new_blocked_faces, current_node.get());
			bfs_order.push(seen_nodes[new_cube] = std::shared_ptr<Tree::Node>(new_node));
			
			if (opposite_tree.seen_nodes.contains(new_cube)) return new_cube;
		}
	}
	return {};
}

Tree::Tree(const Cube &cube)
:
	root(cube)
{
	bfs_order.push(std::make_shared<Tree::Node>(cube));
	seen_nodes[cube] = bfs_order.front();
}

std::vector<std::string> solve(const Cube &start_cube, const Cube &end_cube)
{
	Tree start_tree(start_cube);
	Tree end_tree  (end_cube  );

	bool is_start_tree_to_attempt = true;
	std::optional<Cube> meeting_cube = {};
	while (!meeting_cube.has_value())
	{
		if (is_start_tree_to_attempt) meeting_cube = start_tree.attemptReaching(end_tree  );
		else						  meeting_cube = end_tree  .attemptReaching(start_tree);

		is_start_tree_to_attempt = !is_start_tree_to_attempt;
	}

	std::vector<std::string> start_moves = start_tree.seen_nodes[meeting_cube.value()]->getMoveSequence();
	std::vector<std::string> end_moves   = end_tree  .seen_nodes[meeting_cube.value()]->getMoveSequence();
	reverse(end_moves.begin(), end_moves.end());

	std::vector<std::string> res = start_moves;

	auto reverseMove = [](const std::string &move)
	{
		char last_char = move[move.size() - 1];
		if (last_char == '2')  return move;
		if (last_char == '\'') return std::string(1, move[0]);
		return std::string(1, move[0]) + '\'';
	};
	for (std::string &move : end_moves)
		res.push_back(reverseMove(move));

	return res;
}
