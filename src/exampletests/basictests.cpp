#include "simpletest.h"
#include <string.h>

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

DEFINE_TEST_G(MaxErrors, MaxErrors)
{
	TestError const* lastError = nullptr;
	while (GetLastError() != lastError)
	{
		lastError = GetLastError();

		TEST_MESSAGE(false, "This is a really long message that is left intentionally false.");
	}
}

DEFINE_TEST_G(TestMessageSpace, Basic)
{
	bool found = false;
	for (TestFixture* i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
	{
		if (strcmp(i->TestName(), "MaxErrors") == 0 && strcmp(i->TestGroup(), "MaxErrors") == 0)
		{
			i->ExecuteTest();

			int errorCount = 0;
			for (TestError const* err = i->GetFirstError(); err != i->GetLastError(); err = err->next)
			{
				++errorCount;
			}

			TEST_EQ(i->NumErrors(), i->NumTests());
			TEST_EQ(i->NumErrors(), errorCount + 1);

			found = true;
			break;
		}
	}

	TEST(found);
}