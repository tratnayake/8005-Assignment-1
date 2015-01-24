#! /bin/bash
clear


echo $1

echo "Running test $1 times";
testFolder=`date '+%Y_%m_%d__%H_%M_%S'`;
mkdir ./logfiles
echo"Made the logfiles folder" 
mkdir ./logfiles/$testFolder
echo "Made logfiles test results folder";

COUNTER=1
 while [[  $COUNTER -lt $1 ]]; do


	echo "Log file is"
	mkdir "./logfiles"
	today=`date '+%Y_%m_%d__%H_%M_%S'`;
	filename="./logfiles/$testFolder/Threads$today.csv"
	echo $filename;

	echo "Making ThreadFiles folder"

	mkdir ThreadFiles
	sleep 2

	echo "Deleting any previous master log files"

	rm ThreadLogFile.txt

	rm ./ThreadFiles/*.txt



	array=(1000 10000 100000 1000000 10000000)

	echo "Executing experiment with THREADS."
	for ix in ${!array[*]}
	do
			
	     now="$(date +'%T')"
        printf "Test %s THREADS Case  %d :%s hash iterations\n" "$COUNTER" "$ix" "${array[$ix]}"
        printf "Test %s THREADS,Iterations,%s,START,%s" "$COUNTER" "${array[$ix]}" "$now" >> $filename;
        ./ThreadRunner ${array[$ix]}
        printf "Test %s THREADS Case  %d :%s hash iterations FINISHED\n\n" "$COUNTER" "$ix" "${array[$ix]}"
        now="$(date +'%T')"
        printf "Test %s THREADS,Iterations %s,END,%s" "$COUNTER" "${array[$ix]}" "$now" >> $filename;
        sleep 4
	    rm ./ThreadFiles/*.txt

	done
	echo

	COUNTER=$(( $COUNTER + 1 ))
   

 done