#!/bin/bash

toolset=${1}
config=${2}
extra=${3}

#for travis ci we enter here with gcc as the toolset but GCOV env var set
if [[ -v GCOV ]]; then
    toolset=gcov
fi

if [ "$toolset" = "" ]; then
    toolset=gcc
fi
if [ "$config" = "" ]; then
    config=debug
fi

pushd projects
make -f simpletestsolution_linux_${toolset}.make config=${config} ${extra}
exitcode=$?
popd

if [ ${exitcode} = 0 ]; then
    if [ "$extra" != "clean" ]; then
        ./.temp/bin/simpletestproject_linux_${toolset}_${config}
    fi
fi

if [[ -v GCOV ]]; then
    gcov -n -o .temp/build/${config}/simpletestproject_linux_${toolset}/ simpletest/simpletest.cpp src/*.cpp src/exampletests/*.cpp > /dev/null
    bash <(curl -s https://codecov.io/bash)
fi