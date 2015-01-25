#! /bin/bash
#/* ----------------------------------------------------------------------------
#SCRIPT FILE
#
#Name:           Processes.sh
#
#Program:        a1 (COMP 8005, Threads vs Processes)
#
#Developer:      Thilina Ratnayake
#
#Due date:       26 Jan 2015
#
#Description:
#        This script automates the experiment and runs the main source program for the desired amount of iterations
#        and repeats for the desired amount of iterations for experiment CONTROL.
#
#---------------------------------------------------------------------------- *
clear

echo $1

echo "Running test $1 times";
testFolder=`date '+%Y_%m_%d__%H_%M_%S'`;
mkdir ./logfiles/$testFolder
echo "Made logfiles test results folder";

COUNTER=0
 while [[  $COUNTER -lt $1 ]]; do
     
     echo "Log file is"
    mkdir "./logfiles"
    today=`date '+%Y_%m_%d__%H_%M_%S'`;
    filename="./logfiles/$testFolder/Processes$today.csv"
    echo $filename;

    echo "Making ProcessFiles folder"

    mkdir ProcessFiles
    sleep 2

    echo "Deleting any previous master log files"

    rm ProcessLogFile.txt

    rm ./ProcessFiles/*.txt


   array=(1000 10000 100000 1000000 10000000)

    echo "Executing experiment with PROCESSES."
    for ix in ${!array[*]}
    do
        now="$(date +'%T')"
        printf "Test %s PROCESSES Case  %d :%s hash iterations\n" "$COUNTER" "$ix" "${array[$ix]}"
        printf "Test %s PROCESSES,Iterations,%s,START,%s\n" "$COUNTER" "${array[$ix]}" "$now" >> $filename;
        ./ProcessRunner ${array[$ix]}
        printf "Test %s PROCESSES  Case  %d :%s hash iterations FINISHED\n\n" "$COUNTER" "$ix" "${array[$ix]}"
        now="$(date +'%T')"
        printf "Test %s PROCESSES,Iterations,%s,END,%s\n" "$COUNTER" "${array[$ix]}" "$now" >> $filename;
        echo "Show last values"
        tail -n4 ./ProcessFiles/ProcessTaskOutputFile0.txt
        tail -n4 ./ProcessFiles/ProcessTaskOutputFile1.txt
        tail -n4 ./ProcessFiles/ProcessTaskOutputFile2.txt
        tail -n4 ./ProcessFiles/ProcessTaskOutputFile3.txt
        tail -n4 ./ProcessFiles/ProcessTaskOutputFile4.txt

        sleep 4
        rm -r ./ProcessFiles/*.txt


    done
    echo
 
    COUNTER=$(( $COUNTER + 1 ))
    

 done



