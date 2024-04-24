#include "CppUnitTest.h"

#include "red_black_node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace red_black_tree_tests
{
	TEST_CLASS(test_red_black_node)
	{
	public:

		TEST_METHOD(test_minimal_constructor)
		{
			// Call the minimal constructor
			const red_black_node<int> node(691);

			Assert::IsTrue(node.data == 691);
			Assert::IsTrue(node.color == color::black);
			Assert::IsTrue(node.left == nullptr);
			Assert::IsTrue(node.right == nullptr);
			Assert::IsTrue(node.parent == nullptr);
		}

		TEST_METHOD(test_copy_constructor)
		{
			red_black_node<int> node(691);
			node.left = &node;
			node.right = &node;
			node.parent = &node;
			node.color = color::red;

			// Call the copy constructor
			const auto node_copy = node;

			// Assert node is still valid
			Assert::IsTrue(node.data == 691);
			Assert::IsTrue(node.left == &node);
			Assert::IsTrue(node.right == &node);
			Assert::IsTrue(node.parent == &node);
			Assert::IsTrue(node.color == color::red);

			// Assert node_copy == node
			Assert::IsTrue(node_copy.data == node.data);
			Assert::IsTrue(node_copy.left == &node);
			Assert::IsTrue(node_copy.right == &node);
			Assert::IsTrue(node_copy.parent == &node);
			Assert::IsTrue(node_copy.color == color::red);
		}

		TEST_METHOD(test_move_constructor)
		{
			red_black_node<int> node(691);
			node.left = &node;
			node.right = &node;
			node.parent = &node;
			node.color = color::red;

			// Call the copy constructor
			const auto node_copy = std::move(node);

			// Assert node is not valid anymore
			Assert::IsTrue(node.data == 691);
			Assert::IsTrue(node.left == nullptr);
			Assert::IsTrue(node.right == nullptr);
			Assert::IsTrue(node.parent == nullptr);
			Assert::IsTrue(node.color == color::black);

			// Assert node_copy == node
			Assert::IsTrue(node_copy.data == 691);
			Assert::IsTrue(node_copy.left == &node);
			Assert::IsTrue(node_copy.right == &node);
			Assert::IsTrue(node_copy.parent == &node);
			Assert::IsTrue(node_copy.color == color::red);
		}

		TEST_METHOD(test_copy_assignment)
		{
			red_black_node<int> node_0(691);
			node_0.left = &node_0;
			node_0.right = &node_0;
			node_0.parent = &node_0;
			node_0.color = color::red;

			red_black_node<int> node_1(83);

			// Perform copy assignment
			node_1 = node_0;

			// Assert node_0 hasn't changed
			Assert::IsTrue(node_0.data == 691);
			Assert::IsTrue(node_0.left == &node_0);
			Assert::IsTrue(node_0.right == &node_0);
			Assert::IsTrue(node_0.parent == &node_0);
			Assert::IsTrue(node_0.color == color::red);

			// Assert node_1 now has all values from node_0
			Assert::IsTrue(node_1.data == 691);
			Assert::IsTrue(node_1.left == &node_0);
			Assert::IsTrue(node_1.right == &node_0);
			Assert::IsTrue(node_1.parent == &node_0);
			Assert::IsTrue(node_1.color == color::red);
		}

		TEST_METHOD(test_move_assignment)
		{
			red_black_node<int> node_0(691);
			node_0.left = &node_0;
			node_0.right = &node_0;
			node_0.parent = &node_0;
			node_0.color = color::red;

			red_black_node<int> node_1(83);

			// Perform move assignment
			node_1 = std::move(node_0);

			// Assert node is not valid anymore
			Assert::IsTrue(node_0.data == 691);
			Assert::IsTrue(node_0.left == nullptr);
			Assert::IsTrue(node_0.right == nullptr);
			Assert::IsTrue(node_0.parent == nullptr);
			Assert::IsTrue(node_0.color == color::black);

			// Assert node_1 now has all values from node_0
			Assert::IsTrue(node_1.data == 691);
			Assert::IsTrue(node_1.left == &node_0);
			Assert::IsTrue(node_1.right == &node_0);
			Assert::IsTrue(node_1.parent == &node_0);
			Assert::IsTrue(node_1.color == color::red);
		}

	};
}