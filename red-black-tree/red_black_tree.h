#pragma once

#include "red_black_node.h"

#include <queue>

namespace {

	template <typename t>
	struct red_black_tree;

}

namespace utils {

	template <typename t>
	color get_color(
		tree_node<t>* node) {

		// Nil nodes are always black
		if (!node) return color::black;

		return static_cast<red_black_node<t>*>(node)->color;

	}

	template <typename t>
	void set_color(
		tree_node<t>* node,
		color color) {

		if (!node) return;

		static_cast<red_black_node<t>*>(node)->color = color;

	}

	template <typename t>
	void rotate_left(
		red_black_tree<t>& tree,
		red_black_node<t>* const node) {

		//	   \ /			   \ /
		//		n				y
		//	   / \			   / \
		//	  a	  y		=>	  n	  c
		//		 / \		 / \
		//		b	c		a	b

		if (!node->right) return;


		// Alias nodes //

		auto n = node;
		auto y = static_cast<red_black_node<t>*>(n->right);


		// Transfer b to n //

		n->right = y->left;
		if(y->left)
			static_cast<red_black_node<t>*>(y->left)->parent = n;


		// Connect y with the parent of n //

		y->parent = n->parent;

		if (n->parent == nullptr) {
			tree.root = y;
		}

		else if (n == n->parent->left) {
			n->parent->left = y;
		}

		else {
			n->parent->right = y;
		}


		// Make y the parent of n //

		y->left = n;
		n->parent = y;

	}

	template <typename t>
	void rotate_right(
		red_black_tree<t>& tree,
		red_black_node<t>* const node) {

		//	   \ /			   \ /
		//		n				y
		//	   / \			   / \
		//	  y	  c		=>	  a	  n
		//	 / \				 / \
		//	a	b				b	c

		if (!node->left) return;


		// Alias nodes //

		auto n = node;
		auto y = static_cast<red_black_node<t>*>(n->left);


		// Transfer b to n //

		n->left = y->right;
		if(y->right)
			static_cast<red_black_node<t>*>(y->right)->parent = n;


		// Connect y with the parent of n //

		y->parent = n->parent;

		if (n->parent == nullptr) {
			tree.root = y;
		}

		else if (n == n->parent->left) {
			n->parent->left = y;
		}

		else {
			n->parent->right = y;
		}


		// Make y the parent of n //

		y->right = n;
		n->parent = y;

	}

	template <typename t>
	void fix_insert(
		red_black_tree<t>& tree,
		red_black_node<t>* node) {

		// node initially is the node that was inserted into the tree
		red_black_node<t>* parent = nullptr;
		red_black_node<t>* grandparent = nullptr;

		// While the current node is not the root
		// and the current node and its parent are red (two consecutive red nodes)
		//
		//		  rp		   rp
		//		 /		or		\
		//		rn				 rn
		//
		while (node != tree.root &&
			get_color(node) == color::red &&
			get_color(node->parent) == color::red) {

			parent = node->parent;
			grandparent = parent->parent;

			// If the parent is the left child of the grandparent
			//
			//	   *g
			//	   /
			//	  rp
			//
			if (parent == grandparent->left) {

				// Set the uncle of the parent to the grandparent's right
				auto uncle = static_cast<red_black_node<t>*>(grandparent->right);

				// If the uncle is red
				//
				//		*g
				//	   /  \
				//	  rp   ru
				//
				if (get_color<t>(uncle) == color::red) {

					// Recolor the grandparent red and it's direct descendants black
					//
					//		rg
					//	   /  \
					//	  bp   bu
					//
					set_color(grandparent, color::red);
					set_color(uncle, color::black);
					set_color(parent, color::black);

					// Proceed to the grandparent and continue to the next iteration
					node = grandparent;

				}

				// If the uncle is black
				//
				//		*g
				//	   /  \
				//	  rp   bu
				//
				else {

					// If the current node is the right child of it's parent
					//
					//		*g
					//	   /  \
					//	  rp   bu
					//	   \
					//	   rn
					//
					if (node == parent->right) {

						// Rotate the parent left
						//
						//		*g
						//	   /  \
						//	  rn   bu
						//	 /
						//	rp
						//
						rotate_left<t>(tree, parent);

						// Swap node and parent trackers
						//
						//		*g
						//	   /  \
						//	  rp   bu
						//	 /
						//	rn
						//
						node = parent;
						parent = node->parent;

					}

					// Rotate the grandparent right
					//
					//		rp
					//	   /  \
					//	  rn   *g
					//			\
					//			bu
					//
					rotate_right<t>(tree, grandparent);

					// Swap the colors of the parent and the grandparent
					//
					//		*p
					//	   /  \
					//	  rn   rg
					//			\
					//			bu
					//
					std::swap(parent->color, grandparent->color);

					// Proceed to the parent and continue to the next iteration
					node = parent;

				}
			}

			// If the parent is the right child of the grandparent
			//
			//	   *g
			//		\
			//		rp
			//
			else if(parent == grandparent->right) {

				// Set the uncle of the parent to the grandparent's left
				auto uncle = static_cast<red_black_node<t>*>(grandparent->left);

				// If the uncle is red
				//
				//		*g
				//	   /  \
				//	  ru   rp
				//
				if (get_color(uncle) == color::red) {

					// Recolor the grandparent red and it's direct descendants black
					//
					//		rg
					//	   /  \
					//	  bu   bp
					//
					set_color(grandparent, color::red);
					set_color(uncle, color::black);
					set_color(parent, color::black);

					// Proceed to the grandparent and continue to the next iteration
					node = grandparent;

				}

				// If the uncle is black
				//
				//		*g
				//	   /  \
				//	  bu   rp
				//
				else {

					// If the current node is the left child of it's parent
					//
					//		*g
					//	   /  \
					//	  bu   rp
					//		   /
					//		  rn
					//
					if (node == parent->left) {

						// Rotate the parent right
						//
						//		*g
						//	   /  \
						//	  bu   rn
						//			\
						//			rp
						//
						rotate_right(tree, parent);

						// Swap node and parent trackers
						//
						//		*g
						//	   /  \
						//	  bu   rp
						//			\
						//			rn
						//
						node = parent;
						parent = node->parent;

					}

					// Rotate the grandparent left
					//
					//		rp
					//	   /  \
					//	  *g   rn
					//	 /
					//	bu
					//
					rotate_left(tree, grandparent);

					// Swap the colors of the parent and the grandparent
					//
					//		*p
					//	   /  \
					//	  rg   rn
					//	 /
					//	bu
					//
					std::swap(parent->color, grandparent->color);

					// Proceed to the parent and continue to the next iteration
					node = parent;

				}

			}

		}

		// Recolor the root black (it might've become red through a rotation)
		set_color(tree.root, color::black);

	}

	template <typename t>
	void fix_delete(
		red_black_tree<t>& tree,
		red_black_node<t>* node,
		red_black_node<t>* node_parent,
		bool node_is_left) {

		// While the current node is not the root
		// and the node's color is black (double black condition)
		//
		//		  bp		   bp
		//	 	 /		or		\
		//		bn				 bn
		//
		while (node != tree.root &&
			get_color(node) == color::black) {

			// If the node is the left child of it's parent
			//
			//		bp
			//	 	/
			//	   bn
			//
			if (node_is_left) {

				// Set the uncle to the right sibling of the node's parent
				auto uncle = static_cast<red_black_node<t>*>(node_parent->right);

				// If the uncle is red
				//
				//		bp
				//	   /  \
				//	  bn   ru
				//
				if (get_color(uncle) == color::red) {

					// Re-color and rotate left
					//
					//		  bu
					//		 /
					//		rp
					//	   /
					//	  bn
					//
					set_color(uncle, color::black);
					set_color(node_parent, color::red);
					rotate_left(tree, node_parent);

					// Re-set the uncle after the rotation
					uncle = static_cast<red_black_node<t>*>(node_parent->right);

				}

				// If both the uncle's children are black
				//
				//		bp
				//	   /  \
				//	  bn   *u
				//		  /  \
				//		 b0	  b1
				//
				if (get_color(uncle->left) == color::black &&
					get_color(uncle->right) == color::black) {

					// Set the uncle's color to red
					set_color(uncle, color::red);

					// Proceed to the node's parent
					node = node_parent;
					node_parent = node->parent;

					// Determine if the parent proceeded to is a left or right child
					node_is_left = (node_parent != nullptr && node == node_parent->left);

				}

				// If either one, or both of the uncle's children are red
				else {

					// If the uncle's right child is black
					//
					//		bp
					//	   /  \
					//	  bn   *u
					//		  /  \
					//		 r0	  b1
					//
					if (get_color(uncle->right) == color::black) {

						// Re-color and rotate right
						//
						//		bp
						//	   /  \
						//	  bn   b0
						//		     \
						//			 ru
						//			   \
						//			   b1
						//
						set_color(uncle->left, color::black);
						set_color(uncle, color::red);
						rotate_right(tree, uncle);

						// Re-set the uncle after the rotation
						uncle = static_cast<red_black_node<t>*>(node_parent->right);

					}

					// Re-color and rotate left
					//
					//  		bu
					//  	   /  \
					//  	  bp   b1
					//  	 /  \
					//	    bn   b0
					//
					set_color(uncle, node_parent->color);
					set_color(node_parent, color::black);
					set_color(uncle->right, color::black);
					rotate_left(tree, node_parent);

					// Set the node to root
					node = tree.root;

					// Set the node's parent to nullptr
					node_parent = nullptr;

				}

			}

			// If the node is the left child of it's parent
			//
			//		bp
			//	 	 \
			//		  bn
			//
			else {

				// Set the uncle to the left sibling of the node's parent
				auto uncle = static_cast<red_black_node<t>*>(node_parent->left);

				// If the uncle is red
				//
				//		bp
				//	   /  \
				//	  ru   bn
				//
				if (get_color(uncle) == color::red) {

					// Re-color and rotate right
					//
					//		bu
					//		  \
					//		  rp
					//			\
					//			bn
					//
					set_color(uncle, color::black);
					set_color(node_parent, color::red);
					rotate_right(tree, node_parent);

					// Re-set the uncle after the rotation
					uncle = static_cast<red_black_node<t>*>(node_parent->left);

				}

				// If both the uncle's children are black
				//
				//			bp
				//	   	   /  \
				//   	 *u	   bn
				//		/  \
				//	   b0   b1
				//
				if (get_color(uncle->right) == color::black &&
					get_color(uncle->left) == color::black) {

					// Set the uncle's color to red
					set_color(uncle, color::red);

					// Proceed to the node's parent
					node = node_parent;
					node_parent = node->parent;

					// Determine if the parent proceeded to is a left or right child
					node_is_left = (node_parent != nullptr && node == node_parent->left);

				}

				// If either one, or both of the uncle's children are red
				else {

					// If the uncle's left child is black
					//
					//			bp
					//	   	   /  \
					//   	 *u	   bn
					//		/  \
					//	   b0   r1
					//
					if (get_color(uncle->left) == color::black) {

						// Re-color and rotate left
						//
						//			bp
						//	   	   /  \
						//   	  b1   bn
						//		 /
						//	    ru
						//	   /
						//	  b0
						//
						set_color(uncle->right, color::black);
						set_color(uncle, color::red);
						rotate_left(tree, uncle);

						// Re-set the uncle after the rotation
						uncle = static_cast<red_black_node<t>*>(node_parent->left);

					}

					// Re-color and rotate right
					//
					//		bu
					//	   /  \
					//	  b0   bp
					//		  /  \
					//		 b1	  bn
					//
					set_color(uncle, node_parent->color);
					set_color(node_parent, color::black);
					set_color(uncle->left, color::black);
					rotate_right(tree, node_parent);

					// Set the node to root
					node = tree.root;

					// Set the node's parent to nullptr
					node_parent = nullptr;

				}

			}

		}

		// Set the node's color to black
		set_color(node, color::black);

	}

	template <typename t>
	tree_node<t>* get_maximum_node(
		tree_node<t>* node) {

		while (node->right)
			node = node->right;

		return node;

	}

}

namespace {

	template <typename t>
	struct red_black_tree {

		red_black_node<t>* root;

		red_black_tree() :

			root(nullptr) {}

		// Copy constructor
		red_black_tree(
			const red_black_tree& other) = delete;

		// Move constructor
		red_black_tree(
			red_black_tree&& other) = delete;

		// Destructor
		~red_black_tree() {

			if (!this->root) return;

			// Level order traversal 
			std::queue<red_black_node<t>*> node_queue;
			node_queue.push(this->root);

			while (!node_queue.empty()) {

				auto current_node = node_queue.front();
				node_queue.pop();

				if (current_node->left != nullptr)
					node_queue.push(static_cast<red_black_node<t>*>(current_node->left));

				if (current_node->right != nullptr)
					node_queue.push(static_cast<red_black_node<t>*>(current_node->right));

				delete current_node;

			}

		}

		// Copy assignment
		red_black_tree& operator=(
			const red_black_tree& other) = delete;

		// Move assignment
		red_black_tree& operator=(
			red_black_tree&& other) = delete;

	};

	template <typename t>
	void insert(
		const t data,
		red_black_tree<t>& tree) {

		// If tree empty, insert first node //

		if (!tree.root) {
			tree.root = new red_black_node<t>(data);
			return;
		}


		// Find a parent leaf node for the new node //

		tree_node<t>* current_node = tree.root;
		tree_node<t>* parent = nullptr;

		while (current_node) {

			parent = current_node;

			if (data < current_node->data) {
				current_node = current_node->left;
			}

			else if (data > current_node->data) {
				current_node = current_node->right;
			}

			else {
				throw std::runtime_error("Duplicate entry not supported");
			}

		}


		// Add a new node to the leaf //

		auto new_node = new red_black_node<t>(data);
		new_node->color = color::red;

		if (data < parent->data) {
			parent->left = new_node;
		}

		else {
			parent->right = new_node;
		}

		new_node->parent = static_cast<red_black_node<t>*>(parent);


		// Rebalance the tree if necessary //

		utils::fix_insert<t>(tree, new_node);

	}

	template <typename t>
	bool remove(
		const t data,
		red_black_tree<t>& tree) {

		// Find the node to remove //

		auto target_node = tree.root;

		while (target_node) {

			if (data < target_node->data) {
				target_node = static_cast<red_black_node<t>*>(target_node->left);
			}

			else if (data > target_node->data) {
				target_node = static_cast<red_black_node<t>*>(target_node->right);
			}

			else {
				break;
			}

		}

		if (!target_node) {
			return false;
		}


		// Select a node to delete //

		red_black_node<t>* to_be_deleted = nullptr;

		// If the target node has at most 1 child
		if (!target_node->left || !target_node->right) {

			// Mark the target_node for deletion
			to_be_deleted = target_node;

		}

		// If the target node has two children
		else {

			// Mark the left tree's max node for deletion
			to_be_deleted = static_cast<red_black_node<t>*>(utils::get_maximum_node(target_node->left));

		}


		// Get a handle to the child of the node to delete //

		auto child = to_be_deleted->left ?
			static_cast<red_black_node<t>*>(to_be_deleted->left) :
			static_cast<red_black_node<t>*>(to_be_deleted->right);


		// Connect the child to it's grandparent //

		// Set the child's parent to it's grandparent
		if (child) {
			child->parent = to_be_deleted->parent;
		}

		bool child_is_left = false;

		// If the node to be deleted is the root node
		if (!to_be_deleted->parent) {

			// Let the child be the new root
			tree.root = child;

		}

		// If the node to be deleted is it's parent's left child
		else if (to_be_deleted == to_be_deleted->parent->left) {

			// Set the parent's left child to child
			to_be_deleted->parent->left = child;
			child_is_left = true;

		}

		// If the node to be deleted is it's parent's right child
		else if(to_be_deleted == to_be_deleted->parent->right) {

			// Set the parent's right child to child
			to_be_deleted->parent->right = child;
			child_is_left = false;

		}


		// Transfer payload to the target node //

		if (to_be_deleted != target_node) {
			target_node->data = to_be_deleted->data;
		}


		// Rebalance //

		const auto child_parent = to_be_deleted->parent;

		if (utils::get_color(to_be_deleted) == color::black && child_parent) {
			utils::fix_delete<t>(tree, child, child_parent, child_is_left);
		}


		// Release memory //

		delete to_be_deleted;

		return true;

	}

	template <typename t>
	bool find(
		const t data,
		red_black_tree<t>& tree) {

		tree_node<t>* current_node = tree.root;

		while (current_node) {

			if (data == current_node->data) {
				return true;
			}

			if (data < current_node->data) {
				current_node = current_node->left;
			}

			else {
				current_node = current_node->right;
			}

		}

		return false;

	}

}