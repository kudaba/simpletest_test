#include "simpletest.h"
#include <string.h>

class ExceptionFixture : public TestFixture
{
public:
	bool ExecuteTest() override
	{
		try
		{
			return TestFixture::ExecuteTest();
		}
		catch (const char* message)
		{
			TEST_ERROR_("Exception caught", "%s", message);
		}
		catch (...)
		{
			TEST_ERROR_("Exception caught", "Unknown exception");
		}
		return false;
	}
};

class ExceptionSetupFixture : public ExceptionFixture
{
public:
	void Setup() override
	{
		throw "Setup";
	}
};

class ExceptionTearDownFixture : public ExceptionFixture
{
public:
	void TearDown() override
	{
		throw "TearDown";
	}
};

DEFINE_TEST_GF(ExceptionSetup, Exceptions, ExceptionSetupFixture)
{
	throw "Function";
}

DEFINE_TEST_GF(ExceptionTearDown, Exceptions, ExceptionTearDownFixture)
{
	throw "Function";
}

DEFINE_TEST_GF(ExceptionString, Exceptions, ExceptionFixture)
{
	throw "Function";
}

DEFINE_TEST_GF(ExceptionInt, Exceptions, ExceptionSetupFixture)
{
	throw 5;
}

DEFINE_TEST(ExceptionTests)
{
	for (auto i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
	{
		if (strcmp("Exceptions", i->TestGroup()) == 0)
		{
			TEST(!i->ExecuteTest());
			TEST_EQ(i->NumTests(), 1);
			TEST_EQ(i->NumErrors(), 1);

			if (i == &ExceptionsExceptionSetupInstance)
				TEST(strstr(i->GetFirstError()->message, "Setup") != nullptr);
			else if (i == &ExceptionsExceptionTearDownInstance)
				TEST(strstr(i->GetFirstError()->message, "TearDown") != nullptr);
			else if (i == &ExceptionsExceptionStringInstance)
				TEST(strstr(i->GetFirstError()->message, "Function") != nullptr);
			else
				TEST(strstr(i->GetFirstError()->message, "Unknown") != nullptr);
		}
	}
}