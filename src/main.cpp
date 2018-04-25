#include "simpletest.h"

int main()
{
	bool pass = true;
	pass &= TestFixture::ExecuteTestGroup("Basic", TestFixture::Verbose);
	pass &= TestFixture::ExecuteTestGroup("Memory", TestFixture::Verbose);
	pass &= TestFixture::ExecuteTestGroup("Global", TestFixture::Verbose);
	return pass ? 0 : 1;
}
