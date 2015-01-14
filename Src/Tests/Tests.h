#ifndef _t3d_TEST_MAIN_H
#define _t3d_TEST_MAIN_H

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


#define FOR_TIMES(i, count) for (int i=0; i<count; ++i)


#define ASSERT_NULL(what) ASSERT_TRUE(what == nullptr)
#define ASSERT_NOT_NULL(what) ASSERT_FALSE(what == nullptr)

#endif
