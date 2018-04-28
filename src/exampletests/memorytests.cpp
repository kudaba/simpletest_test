#include "simpletest.h"
#include <memory>
#include <atomic>

static std::atomic<uint64> locAllocationCount;
static std::atomic<uint64> locTotalAllocations;

size_t AllocationCount()
{
	return locAllocationCount;
}

void* operator new(size_t size) throw(std::bad_alloc)
{
	++locAllocationCount;
	++locTotalAllocations;
	return malloc(size);
}

void operator delete(void* data) noexcept
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
	uint64 allocs = locTotalAllocations;
	TestFixture::ExecuteTestGroup("BasicTests", TestFixture::Silent);
	TEST_EQ(allocs, locTotalAllocations);
}
