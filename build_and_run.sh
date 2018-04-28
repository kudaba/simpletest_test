#!/bin/bash

toolset=${1}
config=${2}

if [ "$toolset" = "" ]; then
    toolset=gcc
fi
if [ "$config" = "" ]; then
    config=debug
fi

pushd projects
make -f simpletestsolution_linux_${toolset}.make config=${config}
popd
./.temp/bin/simpletestproject_linux_${toolset}_${config}
