#include "Tree.hpp"

const std::string NO_MOVE = " ";

Tree::TreeNode::TreeNode(const Cube &cube, const std::string &move = NO_MOVE, int blocked_faces = 0, const TreeNode *parent = nullptr)
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
	bfs_order.push(&root);
}
