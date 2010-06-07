#!/bin/sh

# This is a nasty workaround of a CTest limitation
# of setting the environment variables for the test.

# $1: LD_LIBRARY_PATH
# $2: $PYTHONPATH
# $3: python executable
# $4: test file

export LD_LIBRARY_PATH=$1:$LD_LIBRARY_PATH
export PYTHONPATH=$2:$PYTHONPATH
$3 $4
