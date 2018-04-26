#include "simpletest.h"
#include <string.h>

DEFINE_TEST_G(TestBool, Fail)
{
	bool truth = true;
	bool lie = false;
	TEST(!truth);
	TEST(lie);
	TEST_MESSAGE(!!lie, "Not not lie is truth");
}

template<typename numtype>
void TestFailNum()
{
	numtype one = 1;
	numtype five = 5;
	numtype ten = 10;

	TEST_EQ(one, five);
	TEST_NEQ(one, one);

	TEST_GREATER(five, ten);
	TEST_LESS(five, one);

	TEST_GREATER_EQUAL(five, ten);
	TEST_LESS_EQUAL(five, one);
}

DEFINE_TEST_G(TestInt, Fail)
{
	TestFailNum<int>();
	TestFailNum<__int64>();
	TestFailNum<unsigned int>();
	TestFailNum<unsigned __int64>();
}

DEFINE_TEST_G(TestFloat, Fail)
{
	TestFailNum<float>();
	TestFailNum<double>();

	TEST_CLOSE(10.0f, 11.0f, 0.0f);
	TEST_CLOSE(10.0, 10.001, 0.00001);
}

DEFINE_TEST(FullFailTest)
{
	for (auto i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
	{
		if (_stricmp("Fail", i->TestGroup()) == 0)
		{
			TEST(!i->ExecuteTest());
			TEST_EQ(i->NumTests(), i->NumErrors());
		}
	}
}