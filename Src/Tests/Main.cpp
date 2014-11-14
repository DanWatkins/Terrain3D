#include <math.h>
#include <gtest/gtest.h>

TEST(test_case_name, test_name)
{
	for (int i=0; i<10; i++)
	{
		float xyz = sin(i);
		printf("xyz is %.02f\n", xyz);
	}

	ASSERT_TRUE(true);
}

TEST(test_case_name2, test_name2)
{
	ASSERT_TRUE(true);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
