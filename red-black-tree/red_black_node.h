#pragma once

#include "tree_node.h"

namespace {

	enum class color : bool {
		red = true,
		black = false
	};

	template <typename t>
	struct red_black_node : public tree_node<t> {

		color color;
		red_black_node<t>* parent;

		// Minimal constructor
		red_black_node(
			t data) noexcept :

			tree_node<t>(data),
			color(color::black),
			parent(nullptr) {}

		// Copy constructor
		red_black_node(
			const red_black_node& other) noexcept :

			tree_node<t>(other),
			color(other.color),
			parent(other.parent) {}

		// Move constructor
		red_black_node(
			red_black_node&& other) noexcept :

			tree_node<t>(std::move(other)),
			color(other.color),
			parent(other.parent) {

			other.color = color::black;
			other.parent = nullptr;

		}

		// Destructor
		~red_black_node() noexcept {}

		// Copy assignment
		red_black_node& operator=(
			const red_black_node& other) noexcept {

			if (this == &other) return *this;

			tree_node<t>::operator=(other);
			this->color = other.color;
			this->parent = other.parent;

			return *this;

		}

		// Move assignment
		red_black_node& operator=(
			red_black_node&& other) noexcept {
		
			if (this == &other) return *this;

			tree_node<t>::operator=(std::move(other));
			this->color = other.color;
			this->parent = other.parent;

			other.color = color::black;
			other.parent = nullptr;

			return *this;

		}

	};

}