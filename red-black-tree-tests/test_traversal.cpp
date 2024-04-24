#include "CppUnitTest.h"

#include "traversal.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace red_black_tree_tests
{
	TEST_CLASS(test_traversal)
	{
	public:

		red_black_tree<int> tree;

		test_traversal()
		{
			//				b3
			//		b1				b5
			//	b0		b2		b4			r7
			//							b6		b8
			//										r9

			insert<int>(0, this->tree);
			insert<int>(1, this->tree);
			insert<int>(2, this->tree);
			insert<int>(3, this->tree);
			insert<int>(4, this->tree);
			insert<int>(5, this->tree);
			insert<int>(6, this->tree);
			insert<int>(7, this->tree);
			insert<int>(8, this->tree);
			insert<int>(9, this->tree);
		}

		TEST_METHOD(test_traverse_in_order)
		{
			const std::vector<int> expected_result = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			std::vector<int> result = {};

			traverse_in_order<int>(this->tree, [&result](const auto& data) {
				result.push_back(data);
			});

			Assert::IsTrue(result == expected_result);
		}

		TEST_METHOD(test_traverse_pre_order)
		{
			const std::vector<int> expected_result = { 3, 1, 0, 2, 5, 4, 7, 6, 8, 9 };

			std::vector<int> result = {};

			traverse_pre_order<int>(this->tree, [&result](const auto& data) {
				result.push_back(data);
			});

			Assert::IsTrue(result == expected_result);
		}

		TEST_METHOD(test_traverse_post_order)
		{
			const std::vector<int> expected_result = { 0, 2, 1, 4, 6, 9, 8, 7, 5, 3 };

			std::vector<int> result = {};

			traverse_post_order<int>(this->tree, [&result](const auto& data) {
				result.push_back(data);
			});

			Assert::IsTrue(result == expected_result);
		}

		TEST_METHOD(test_traverse_level_order)
		{
			const std::vector<int> expected_result = { 3, 1, 5, 0, 2, 4, 7, 6, 8, 9 };

			std::vector<int> result = {};

			traverse_level_order<int>(this->tree, [&result](const auto& data) {
				result.push_back(data);
			});

			Assert::IsTrue(result == expected_result);
		}

	};
}