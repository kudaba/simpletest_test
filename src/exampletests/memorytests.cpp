#include "simpletest.h"
#include <memory>

static size_t locAllocationCount;
static size_t locTotalAllocations;

size_t AllocationCount()
{
	return locAllocationCount;
}

void* operator new(size_t size)
{
	++locAllocationCount;
	++locTotalAllocations;
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

DEFINE_TEST_GF(TestNothing, Memory, MemoryFixture)
{

}

DEFINE_TEST_GF(TestAllocation, Memory, MemoryFixture)
{
	int* intptr = new int;
	TEST_EQ(locAllocationCount, 1);
	delete intptr;
}

DEFINE_TEST_GF(TestBasicTests, Memory, MemoryFixture)
{
	size_t allocs = locTotalAllocations;
	TestFixture::ExecuteTestGroup("BasicTests", TestFixture::Silent);
	TEST_EQ(allocs, locTotalAllocations);
}
