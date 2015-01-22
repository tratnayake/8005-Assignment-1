#! /bin/bash

echo "Deleting any previous master log files"

rm ProcessLogFile.txt

rm ./ProcessFiles/ *.txt


array=(1000 10000 100000 1000000 10000000 100000000 1000000000);

echo "Executing experiment with PROCESSES."
for ix in ${!array[*]}
do

    printf " Case  %d :%s hash iterations\n" "$ix" "${array[$ix]}"
    ./ProcessRunner ${array[$ix]}
    printf " Case  %d :%s hash iterations FINISHED\n\n" "$ix" "${array[$ix]}"
    echo "Check that the last line was of %s iterations" "${array[$ix]}"
    tail -n 5 ./ProcessFiles/ProcessTaskOutputFile0.txt
    sleep 4

done
echo

