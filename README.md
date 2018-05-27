# simpletest_test

[![Build Status](https://travis-ci.org/kudaba/simpletest_test.svg?branch=master)](https://travis-ci.org/kudaba/simpletest_test)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/kudaba/simpletest_test?branch=master&svg=true)](https://ci.appveyor.com/project/kudaba/simpletest-test)
[![codecov](https://codecov.io/gh/kudaba/simpletest_test/branch/master/graph/badge.svg)](https://codecov.io/gh/kudaba/simpletest_test)
<a href="https://scan.coverity.com/projects/kudaba-simpletest_test">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/15803/badge.svg"/>
</a>

This repo functions as both the unit tests for simple tests and shows examples of different ways it can be customized to your needs. To add simpletest to your project you use the [simpletest](https://github.com/kudaba/simpletest) repo as a submodule and it only contains the minimum amount of files. I hope to eventually add a nuget package as well.

## Compiling simpletest_test

Hopefully the last person to make changes has left the sample projects in place. So you should be able to just open the appropriate one and hit compile. As of this writing simpletest has only been tested on windows using Visual Studio 2017 and clang (linux cpp11).

## Generating Projects

I've chosen to use [Sharpmake](https://github.com/ubisoftinc/Sharpmake) as a basis for generating projects. It's a wondering system that makes managing even the most complex projects a breeze and can be used to quickly retarget projects to different build systems and IDEs. As I get access to more development environments I'll generate and test more options.

To regenerate the projects simply run generate_projects.bat in the root directory and open the appropriate projects file in the projects folders.

# Types of tests

I've added a few tests for the system itself, but the most interesting bits are the tests which show the different ways it can be used. Here's a summary:
* basictests.cpp - Test that all the different TEST macros compile properly and don't report issues on correct data.
* exceptiontests.cpp - Shows how Fixtures can be used to capture and report exceptions since that feature isn't part of the core system.
* failtests.cpp - These tests are the invert of basictests and are actually only executed by other tests to ensure the error reporting is working correctly.
* memorytests.cpp - Used to ensure that no allocations occur during the testing process. As of this writing the only heap allocation in the program comes from one of these tests.
* threadingtests.cpp - Shows how tests can easily be multithreaded.

# Future plans / todo
* Hook up travis-ci.org to auto build and test projects.
* Add nuget project