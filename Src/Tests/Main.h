#include <gtest/gtest.h>

/**
 * First #define a class identifier. Then declare this followed
 * by a brace enclosed class declaration.
 */
#define TEST_CLASS \
	class CLASS : public ::testing::Test

/**
 * After declaring a TEST_CLASS in the same file, declare single
 * test cases with TEST_CASE(testName) followed by a brace enclosed
 * function declaration.
 */
#define TEST_CASE(name) \
	TEST_F(CLASS, name)
