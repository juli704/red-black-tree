#include "CppUnitTest.h"

#include "red_black_tree.h"
#include "traversal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace red_black_tree_tests
{
	typedef red_black_node<int> node;

	TEST_CLASS(test_red_black_tree)
	{
	public:

		TEST_METHOD(test_rotate_left)
		{
			// Create tree //

			//	   \ /
			//		n
			//	   / \
			//	  a	  y
			//		 / \
			//		b	c

			auto a = new node(0);
			auto b = new node(0);
			auto c = new node(0);

			auto y = new node(0);

			y->left = b;
			b->parent = y;

			y->right = c;
			c->parent = y;

			auto n = new node(0);

			n->left = a;
			a->parent = n;

			n->right = y;
			y->parent = n;

			red_black_tree<int> tree;
			tree.root = n;


			// Rotate //

			utils::rotate_left<int>(tree, tree.root);


			// Assert //

			//	   \ /
			//		y
			//	   / \
			//	  n	  c
			//	 / \
			//	a	b

			// Assert y's peers
			Assert::IsTrue(tree.root == y);
			Assert::IsTrue(y->parent == nullptr);
			Assert::IsTrue(y->right == c);
			Assert::IsTrue(y->left == n);

			// Assert n's peers
			Assert::IsTrue(n->parent == y);
			Assert::IsTrue(n->right == b);
			Assert::IsTrue(n->left == a);

			// Assert a's peers
			Assert::IsTrue(a->parent == n);
			Assert::IsTrue(a->right == nullptr);
			Assert::IsTrue(a->left == nullptr);

			// Assert c's peers
			Assert::IsTrue(c->parent == y);
			Assert::IsTrue(c->right == nullptr);
			Assert::IsTrue(c->left == nullptr);

			// Assert b's peers
			Assert::IsTrue(b->parent == n);
			Assert::IsTrue(b->right == nullptr);
			Assert::IsTrue(b->left == nullptr);
		}

		TEST_METHOD(test_rotate_right)
		{
			// Create tree //

			//	   \ /
			//		n
			//	   / \
			//	  y	  c
			//	 / \
			//	a	b

			auto a = new node(0);
			auto b = new node(0);
			auto c = new node(0);

			auto y = new node(0);

			y->left = a;
			a->parent = y;

			y->right = b;
			b->parent = y;

			auto n = new node(0);

			n->left = y;
			y->parent = n;

			n->right = c;
			c->parent = n;

			red_black_tree<int> tree;
			tree.root = n;


			// Rotate //

			utils::rotate_right<int>(tree, tree.root);


			// Assert //

			//	   \ /
			//		y
			//	   / \
			//	  a	  n
			//		 / \
			//		b	c

			// Assert y's peers
			Assert::IsTrue(tree.root == y);
			Assert::IsTrue(y->parent == nullptr);
			Assert::IsTrue(y->right == n);
			Assert::IsTrue(y->left == a);

			// Assert n's peers
			Assert::IsTrue(n->parent == y);
			Assert::IsTrue(n->right == c);
			Assert::IsTrue(n->left == b);

			// Assert a's peers
			Assert::IsTrue(a->parent == y);
			Assert::IsTrue(a->right == nullptr);
			Assert::IsTrue(a->left == nullptr);

			// Assert b's peers
			Assert::IsTrue(b->parent == n);
			Assert::IsTrue(b->right == nullptr);
			Assert::IsTrue(b->left == nullptr);

			// Assert c's peers
			Assert::IsTrue(c->parent == n);
			Assert::IsTrue(c->right == nullptr);
			Assert::IsTrue(c->left == nullptr);
		}

		TEST_METHOD(test_insert)
		{
			red_black_tree<int> tree;
			this->construct_full_tree(tree);

			const std::vector<int> expected_result = { 5, 2, 7, 1, 3, 6, 9, 0, 4, 8 };

			std::vector<int> result = {};

			traverse_level_order<int>(tree, [&result](const auto& data) {
				result.push_back(data);
			});

			Assert::IsTrue(result == expected_result);
		}

		TEST_METHOD(test_remove)
		{
			red_black_tree<int> tree;
			this->construct_full_tree(tree);

			remove<int>(5, tree);
			remove<int>(1, tree);
			remove<int>(7, tree);
			remove<int>(9, tree);
			remove<int>(0, tree);

			const std::vector<int> expected_result = { 4, 2, 8, 3, 6 };

			std::vector<int> result = {};

			traverse_level_order<int>(tree, [&result](const auto& data) {
				result.push_back(data);
			});

			Assert::IsTrue(result == expected_result);
		}

		TEST_METHOD(test_find)
		{
			red_black_tree<int> tree;
			this->construct_full_tree(tree);

			Assert::IsTrue(find<int>(0, tree));
			Assert::IsTrue(find<int>(1, tree));
			Assert::IsTrue(find<int>(2, tree));
			Assert::IsTrue(find<int>(3, tree));
			Assert::IsTrue(find<int>(4, tree));
			Assert::IsTrue(find<int>(5, tree));
			Assert::IsTrue(find<int>(6, tree));
			Assert::IsTrue(find<int>(7, tree));
			Assert::IsTrue(find<int>(8, tree));
			Assert::IsTrue(find<int>(9, tree));

			Assert::IsFalse(find<int>(10, tree));
			Assert::IsFalse(find<int>(-1, tree));
			Assert::IsFalse(find<int>(-19837777, tree));
			Assert::IsFalse(find<int>(11, tree));
		}

	private:

		void construct_full_tree(
			red_black_tree<int>& tree) {

			//						b5
			//			r2						  r7
			//		b1		b3				b6			b9
			//	r0				r4					r8

			insert<int>(9, tree);
			insert<int>(1, tree);
			insert<int>(2, tree);
			insert<int>(7, tree);
			insert<int>(6, tree);
			insert<int>(3, tree);
			insert<int>(0, tree);
			insert<int>(5, tree);
			insert<int>(4, tree);
			insert<int>(8, tree);

		}
	};
}