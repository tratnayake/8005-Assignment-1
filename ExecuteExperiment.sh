#!/bin/bash


echo "Run the tests $1 times"

echo "Executing processes"
(cd Processes; sh Processes.sh $1)

echo "Executing threads"
(cd Threads; sh Threads.sh $1)