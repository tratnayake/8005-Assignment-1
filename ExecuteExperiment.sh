#! /bin/bash
#/* ----------------------------------------------------------------------------
#SCRIPT FILE
#
#Name:           ExecuteExperiment.sh
#
#Program:        a1 (COMP 8005, Threads vs Processes)
#
#Developer:      Thilina Ratnayake
#
#Due date:       26 Jan 2015
#
#Description:
#        This script automates the experiment by running the processes and threads starter
#		 scripts with the input being the amount of times to repeat the experiment for CONTROL
#---------------------------------------------------------------------------- *
clear
if [ $EUID != 0 ]; then
    echo "You are not SU. Please run this as ROOT or SU to continue"
    exit $?
fi

echo "Please enter the amount of times you would like to run the tests: "
read input_variable
echo "You entered: $input_variable"

echo "Run the tests $input_variable times"

echo "Executing processes"
(cd Processes; sh Processes.sh $input_variable)

echo "Executing threads"
(cd Threads; sh Threads.sh $input_variable)