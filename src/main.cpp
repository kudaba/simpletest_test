#include "simpletest.h"
#include <stdio.h>
#include <string.h>

extern size_t AllocationCount();

char const* groups[] =
{
	"Basic",
	"Memory",
	"Global",
	"Finale",
	"LeakTest"
};

DEFINE_TEST_G(FinalTest, Finale)
{
	for (auto group : groups)
	{
		if (strcmp(group, "Finale") == 0)
			return;

		for (auto test = GetFirstTest(); test; test = test->GetNextTest())
		{
			if (strcmp(test->TestGroup(), group) == 0)
			{
				TEST_NEQ(test->NumTests(), 0);
			}
		}
	}
}

DEFINE_TEST_G(LeakTest, LeakTest)
{
	TEST_MESSAGE(AllocationCount() == 0, "(%d) Memory leaks detected!!!!", AllocationCount());
}

int main()
{	
	bool pass = true;

	for (auto group : groups)
		pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);

	return pass ? 0 : 1;
}
