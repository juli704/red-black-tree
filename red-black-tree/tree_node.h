#pragma once

#include <iostream> // temp

namespace {

	template <typename t>
	struct tree_node {

		t data;
		tree_node<t>* left, * right;

		// Minimal constructor
		tree_node(
			const t data) noexcept :

			data(data),
			left(nullptr),
			right(nullptr) {
		}

		// Copy constructor
		tree_node(
			const tree_node& other) noexcept :

			data(other.data),
			left(other.left),
			right(other.right) {}

		// Move constructor
		tree_node(
			tree_node&& other) noexcept :

			data(other.data),
			left(other.left),
			right(other.right) {

			other.left = nullptr;
			other.right = nullptr;

		}

		// Destructor
		virtual ~tree_node() noexcept {}

		// Copy assignment
		tree_node& operator=(
			const tree_node& other) noexcept {

			if (this == &other) return *this;

			this->data = other.data;
			this->left = other.left;
			this->right = other.right;

			return *this;

		}

		// Move assignment
		tree_node& operator=(
			tree_node&& other) noexcept {

			if (this == &other) return *this;

			this->data = other.data;
			this->left = other.left;
			this->right = other.right;

			other.left = nullptr;
			other.right = nullptr;

			return *this;

		}

	};

}