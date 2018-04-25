#include "simpletest.h"

DEFINE_TEST_G(TestBool, Basic)
{
	bool truth = true;
	bool lie = false;
	TEST(truth);
	TEST(!lie);
	TEST(!!truth);
}

template<typename numtype>
void TestNum()
{
	numtype one = 1;
	numtype five = 5;
	numtype ten = 10;

	TEST_EQ(one, one);
	TEST_NEQ(one, ten);

	TEST_GREATER(five, one);
	TEST_LESS(five, ten);

	TEST_GREATER_EQUAL(five, five);
	TEST_LESS_EQUAL(five, five);
}

DEFINE_TEST_G(TestInt, Basic)
{
	TestNum<int>();
	TestNum<__int64>();
	TestNum<unsigned int>();
	TestNum<unsigned __int64>();
}

DEFINE_TEST_G(TestFloat, Basic)
{
	TestNum<float>();
	TestNum<double>();

	TEST_CLOSE(10.0f, 11.0f, 2.0f);
	TEST_CLOSE(10.0, 10.001, 0.01);
}
