#include "CppUnitTest.h"

#include "tree_node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace red_black_tree_tests
{
	TEST_CLASS(test_tree_node)
	{
	public:

		TEST_METHOD(test_minimal_constructor)
		{
			// Call the minimal constructor
			const tree_node<int> node(691);

			Assert::IsTrue(node.data == 691);
			Assert::IsTrue(node.left == nullptr);
			Assert::IsTrue(node.right == nullptr);
		}

		TEST_METHOD(test_copy_constructor)
		{
			tree_node<int> node(691);
			node.left = &node;
			node.right = &node;

			// Call the copy constructor
			const auto node_copy = node;

			// Assert node is still valid
			Assert::IsTrue(node.data == 691);
			Assert::IsTrue(node.left == &node);
			Assert::IsTrue(node.right == &node);

			// Assert node_copy == node
			Assert::IsTrue(node_copy.data == node.data);
			Assert::IsTrue(node_copy.left == node.left);
			Assert::IsTrue(node_copy.right == node.right);
		}

		TEST_METHOD(test_move_constructor)
		{
			tree_node<int> node(691);
			node.left = &node;
			node.right = &node;

			// Call the move constructor
			const auto moved = std::move(node);

			// Assert node is not valid anymore
			Assert::IsTrue(node.data == 691);
			Assert::IsTrue(node.left == nullptr);
			Assert::IsTrue(node.right == nullptr);

			// Assert moved == previous node
			Assert::IsTrue(moved.data == 691);
			Assert::IsTrue(moved.left == &node);
			Assert::IsTrue(moved.right == &node);
		}

		TEST_METHOD(test_copy_assignment)
		{
			tree_node<int> node_0(691);
			node_0.left = &node_0;
			node_0.right = &node_0;

			tree_node<int> node_1(83);

			// Perform copy assignment
			node_1 = node_0;

			// Assert node_0 hasn't changed
			Assert::IsTrue(node_0.data == 691);
			Assert::IsTrue(node_0.left == &node_0);
			Assert::IsTrue(node_0.right == &node_0);

			// Assert node_1 now has all values from node_0
			Assert::IsTrue(node_1.data == node_0.data);
			Assert::IsTrue(node_1.left == &node_0);
			Assert::IsTrue(node_1.right == &node_0);
		}

		TEST_METHOD(test_move_assignment)
		{
			tree_node<int> node_0(691);
			node_0.left = &node_0;
			node_0.right = &node_0;

			tree_node<int> node_1(83);

			// Perform move assignment
			node_1 = std::move(node_0);

			// Assert node is not valid anymore
			Assert::IsTrue(node_0.data == 691);
			Assert::IsTrue(node_0.left == nullptr);
			Assert::IsTrue(node_0.right == nullptr);

			// Assert node_1 now has all values from node_0
			Assert::IsTrue(node_1.data == node_0.data);
			Assert::IsTrue(node_1.left == &node_0);
			Assert::IsTrue(node_1.right == &node_0);
		}

	};
}