#include "simpletest.h"
#include <string.h>
#include <stdio.h>

struct Bits
{
	int value;

	bool operator == (Bits other)
	{
		return value == other.value;
	}
};

static char const zerostr[] = "00000000000000000000000000000000";
static char const lowstr[] = "00000000000000000000000000000001";
static char const highstr[] = "10000000000000000000000000000000";
static char const maxstr[] = "11111111111111111111111111111111";

TempString TypeToString(Bits bits)
{
	TempString string;
	for (int i = 0; i < 32; ++i)
	{
		if ((bits.value & (1 << (31 - i))) == 0)
			string.myTextBuffer[i] = '0';
		else
			string.myTextBuffer[i] = '1';
	}
	string.myTextBuffer[32] = 0;
	return string;
}

DEFINE_TEST_G(BitFail, TypeToString)
{
	Bits test = { 0 };
	Bits zero = { 0 };

	test.value = 1;

	TEST_EQ(test, zero);

	test.value = 1 << 31;

	TEST_EQ(test, zero);
}

DEFINE_TEST(BitTypeToString)
{
	Bits test = { 0 };
	TempString string = TypeToString(test);
	TEST_MESSAGE(strcmp(*string, zerostr) == 0, "%s != %s", *string, zerostr);

	test.value = -1;
	string = TypeToString(test);
	TEST_MESSAGE(strcmp(*string, maxstr) == 0, "%s != %s", *string, maxstr);
}

DEFINE_TEST(StringTypeToString)
{
	TempString string = TypeToString("customtestfrompointer");
	TEST_MESSAGE(strcmp(*string, "customtestfrompointer") == 0, "%s != %s", *string, "customtestfrompointer");

	void* null = nullptr;
	string = TypeToString(null);
	TEST_MESSAGE(strcmp(*string, "(nullptr)") == 0, "%s != %s", *string, "(nullptr)");

	int value = 5;
	string = TypeToString(&value);
	TEST_MESSAGE(strcmp(*string, "5") == 0, "%s != %s", *string, "5");

	string = TypeToString(&string);
	TEST_MESSAGE(strcmp(*string, "(unknown type)") == 0, "%s != %s", *string, "(unknown type)");
}

template<typename T>
void TestTypeToString(T value, char const* expected)
{
	TempString string = TypeToString(value);
	TEST_MESSAGE(strcmp(*string, expected) == 0, "%s != %s", *string, expected);
}

template<typename T>
void TestUIntValueType()
{
	TestTypeToString<T>(10, "10");
	TestTypeToString<T>(999, "999");
}

template<typename T>
void TestSIntValueType()
{
	TestTypeToString<T>(-10, "-10");
	TestTypeToString<T>(-999, "-999");

	TestUIntValueType<T>();
}

template<typename T>
void TestFloatValueType()
{
	TestTypeToString<T>(T(500.0), "500");
	TestTypeToString<T>(T(10.5), "10.5");
	TestTypeToString<T>(T(0.000001), "0.000001");
	TestTypeToString<T>(T(-500.0), "-500");
	TestTypeToString<T>(T(-10.5), "-10.5");
	TestTypeToString<T>(T(-0.000001), "-0.000001");
}

DEFINE_TEST(CommonTypeToString)
{
	TestSIntValueType<int>();
	TestUIntValueType<uint>();
	TestSIntValueType<int64>();
	TestUIntValueType<uint64>();
	TestFloatValueType<float>();
	TestFloatValueType<double>();

	TestTypeToString(false, "false");
	TestTypeToString(true, "true");
}

DEFINE_TEST(TypeToString)
{
	bool found = false;
	for (auto i = GetFirstTest(); i; i = i->GetNextTest())
	{
		if (strcmp(i->TestName(), "BitFail") == 0 && strcmp(i->TestGroup(), "TypeToString") == 0)
		{
			found = true;

			i->ExecuteTest();
			TEST_EQ(i->NumErrors(), 2);

			TestError const* firstError = i->GetFirstError();
			TEST_MESSAGE(strstr(firstError->message, lowstr) != nullptr, "%s not found int %s", lowstr, firstError->message);
			firstError = firstError->next;
			TEST_MESSAGE(strstr(firstError->message, highstr) != nullptr, "%s not found int %s", highstr, firstError->message);
			break;
		}
	}

	TEST_MESSAGE(found, "Failed to find BitFail test");
}