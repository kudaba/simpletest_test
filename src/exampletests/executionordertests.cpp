#include "simpletest.h"

int testCounter;

DEFINE_TEST_G(FirstTest, Global)
{
	// multiple runs might leave value in a bad state
	TEST_NEQ(testCounter, 1);
	testCounter = 1;
}
DEFINE_TEST_G(SecondTest, Global)
{
	TEST_EQ(testCounter, 1);
	++testCounter;
}
DEFINE_TEST_G(ThirdTest, Global)
{
	TEST_EQ(testCounter, 2);
	++testCounter;
}
DEFINE_TEST_G(FourthTest, Global)
{
	TEST_EQ(testCounter, 3);
	++testCounter;
}
