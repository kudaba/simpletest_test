#!/bin/bash

toolset=${1}
config=${2}
extra=${3}

if [ "$toolset" = "" ]; then
    toolset=gcc
fi
if [ "$config" = "" ]; then
    config=debug
fi

pushd projects
make -f simpletestsolution_linux_${toolset}.make config=${config} ${extra}
popd

if [ "$extra" != "clean" ]; then
    ./.temp/bin/simpletestproject_linux_${toolset}_${config}
fi

