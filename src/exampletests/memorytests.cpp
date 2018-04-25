#include "simpletest.h"
#include <memory>

static size_t locAllocationCount;

void* operator new(size_t size)
{
	++locAllocationCount;
	return malloc(size);
}

void operator delete(void* data)
{
	--locAllocationCount;
	free(data);
}

class MemoryFixture : public TestFixture
{
protected:
	void Setup() override
	{
		TEST_EQ(locAllocationCount, 0);
	}

	void TearDown() override
	{
		TEST_EQ(locAllocationCount, 0);
	}
};

DEFINE_TEST_GF(TestNothing, MemoryTests, MemoryFixture)
{

}

DEFINE_TEST_GF(TestAllocation, MemoryTests, MemoryFixture)
{
	int* intptr = new int;
	TEST_EQ(locAllocationCount, 1);
	delete intptr;
}

DEFINE_TEST_GF(TestBasicTests, MemoryTests, MemoryFixture)
{
	TestFixture::ExecuteTestGroup("BasicTests", TestFixture::Silent);
}
