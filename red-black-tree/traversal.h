#pragma once

#include "red_black_tree.h"

#include <functional>

namespace {

	template <typename t>
	using process = std::function<void(const t& data)>;

	template <typename t>
	void traverse_in_order(
		const tree_node<t>* const node,
		const process<t> process) {

		if (!node) return;

		traverse_in_order<t>(node->left, process);
		process(node->data);
		traverse_in_order<t>(node->right, process);

	}

	template <typename t>
	void traverse_in_order(
		const red_black_tree<t>& tree,
		const process<t> process) {

		traverse_in_order<t>(tree.root, process);

	}

	template <typename t>
	void traverse_pre_order(
		const tree_node<t>* const node,
		const process<t> process) {

		if (!node) return;

		process(node->data);
		traverse_pre_order<t>(node->left, process);
		traverse_pre_order<t>(node->right, process);

	}

	template <typename t>
	void traverse_pre_order(
		const red_black_tree<t>& tree,
		const process<t> process) {

		traverse_pre_order<t>(tree.root, process);

	}

	template <typename t>
	void traverse_post_order(
		const tree_node<t>* const node,
		const process<t> process) {

		if (!node) return;

		traverse_post_order<t>(node->left, process);
		traverse_post_order<t>(node->right, process);
		process(node->data);

	}

	template <typename t>
	void traverse_post_order(
		const red_black_tree<t>& tree,
		const process<t> process) {

		traverse_post_order<t>(tree.root, process);

	}

	template <typename t>
	void traverse_level_order(
		tree_node<t>* node,
		const process<t> process) {

		if (!node) return;

		std::queue<tree_node<t>*> node_queue;
		node_queue.push(node);

		while (!node_queue.empty()) {

			// Dequeue
			const auto current_node = node_queue.front();
			node_queue.pop();

			// Process
			process(current_node->data);

			// Enqueue children
			if (current_node->left) {
				node_queue.push(current_node->left);
			}

			if (current_node->right) {
				node_queue.push(current_node->right);
			}

		}

	}

	template <typename t>
	void traverse_level_order(
		const red_black_tree<t>& tree,
		const process<t> process) {

		traverse_level_order<t>(tree.root, process);

	}

}