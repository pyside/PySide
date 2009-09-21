#!/usr/bin/python

# This is a nasty workaround of a CTest limitation
# of setting the environment variables for the test.

# $1: LD_LIBRARY_PATH
# $2: $PYTHON_PATH
# $3: python executable
# $4: test file

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$1
export PYTHONPATH=$PYTHON_PATH:$2
$3 $4
