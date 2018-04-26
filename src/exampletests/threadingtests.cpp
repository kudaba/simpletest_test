#include "simpletest.h"
#include <string.h>
#include <thread>

class ThreadingFixture : public TestFixture
{
public:
	void StartThread()
	{
		myThread = std::thread([this](){ ExecuteTest(); });
	}

	void Wait()
	{
		myThread.join();
	}

private:
	std::thread myThread;
};

static int locThreadIndex = 0;

DEFINE_TEST_GF(WaitFor1, Threading, ThreadingFixture)
{
	while (locThreadIndex < 1);
	locThreadIndex = 2;
}

DEFINE_TEST_GF(WaitFor2, Threading, ThreadingFixture)
{
	while (locThreadIndex < 2);
	locThreadIndex = 3;
}

DEFINE_TEST_GF(WaitFor3, Threading, ThreadingFixture)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	locThreadIndex = 1;
	while (locThreadIndex < 3);
	locThreadIndex = 4;
}

DEFINE_TEST(ThreadingTest)
{
	locThreadIndex = 0;

	for (auto i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
	{
		if (_stricmp("Threading", i->TestGroup()) == 0)
		{
			ThreadingFixture* threadf = (ThreadingFixture*)i;
			threadf->StartThread();
		}
	}

	for (auto i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
	{
		if (_stricmp("Threading", i->TestGroup()) == 0)
		{
			ThreadingFixture* threadf = (ThreadingFixture*)i;
			threadf->Wait();
		}
	}

	TEST_EQ(locThreadIndex, 4);
}