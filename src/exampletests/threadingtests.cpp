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

static volatile int locThreadIndex = 0;

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
		if (strcmp("Threading", i->TestGroup()) == 0)
		{
			ThreadingFixture* threadf = (ThreadingFixture*)i;
			threadf->StartThread();
		}
	}

	for (auto i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
	{
		if (strcmp("Threading", i->TestGroup()) == 0)
		{
			ThreadingFixture* threadf = (ThreadingFixture*)i;
			threadf->Wait();
		}
	}

	TEST_EQ(locThreadIndex, 4);
}

//---------------------------------------------------------------------------------
// Example of testing code that is expected to crash. This isn't very portable
// so it's not part of the main system.
//---------------------------------------------------------------------------------

#if !defined(WIN64)

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

static void Crash()
{
	__builtin_trap();
}

#define UNIQUE(a) TOK(a, __LINE__)

#define TEST_CRASH(cond) \
pid_t UNIQUE(pid) = fork(); \
if (UNIQUE(pid) == 0) { cond; _exit(0); } else { \
int UNIQUE(status) = 0; wait(&UNIQUE(status)); \
if (!WIFSIGNALED(UNIQUE(status))) TEST_MESSAGE(0 && STR(cond), "Expected %s to crash, but it ran successfully.", STR(cond) ); }

DEFINE_TEST(ForkTest)
{
	pid_t pid = fork();
	
	if (pid == 0)
	{
		Crash();
		_exit(1);
	}
	else
	{
		int status = 0;
		pid_t doneid = wait(&status);
		TEST_EQ(pid, doneid);

		TEST_EQ(WIFEXITED(status), false);
		TEST(WIFSIGNALED(status));
	}

	TEST_CRASH(Crash());
}
#endif