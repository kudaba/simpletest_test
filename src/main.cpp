#include "simpletest.h"
#include <stdio.h>

extern size_t AllocationCount();

int main()
{
	bool pass = true;
	pass &= TestFixture::ExecuteTestGroup("Basic", TestFixture::Verbose);
	pass &= TestFixture::ExecuteTestGroup("Memory", TestFixture::Verbose);
	pass &= TestFixture::ExecuteTestGroup("Global", TestFixture::Verbose);

	if (AllocationCount() != 0)
	{
		printf("Memory leak detected!!!!");
		pass = false;
	}

	return pass ? 0 : 1;
}
