#!/bin/bash
clear

echo $1

echo "Running test $1 times";
testFolder=`date '+%Y_%m_%d__%H_%M_%S'`;
mkdir ./logfiles/$testFolder
echo "Made logfiles test results folder";

COUNTER=1
 while [[  $COUNTER -lt $1 ]]; do
     
     echo "Log file is"
    mkdir "./logfiles"
    today=`date '+%Y_%m_%d__%H_%M_%S'`;
    filename="./logfiles/$testFolder/Processes$today.txt"
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
        printf "Test %s Case  %d :%s hash iterations\n" "$COUNTER" "$ix" "${array[$ix]}"
        printf "Test %s  Iterations %s | START time %s \n" "$COUNTER" "${array[$ix]}" "$now" >> $filename;
        ./ProcessRunner ${array[$ix]}
        printf "Test %s  Case  %d :%s hash iterations FINISHED\n\n" "$COUNTER" "$ix" "${array[$ix]}"
        now="$(date +'%T')"
        printf "Test %s  Iterations %s | END time %s \n" "$COUNTER" "${array[$ix]}" "$now" >> $filename;
        sleep 4
        rm -r ./ProcessFiles/*.txt


    done
    echo
 
    COUNTER=$(( $COUNTER + 1 ))
    

 done



