#! /bin/bash
clear

echo "Deleting any previous master log files"

rm ThreadLogFile.txt

rm ./ThreadFiles/ *.txt



array=(1000 10000 100000 1000000 10000000 100000000 1000000000);

echo "Executing experiment with THREADS."
for ix in ${!array[*]}
do
		
    printf " Case  %d :%s hash iterations\n" "$ix" "${array[$ix]}"
    ./ThreadRunner ${array[$ix]}
    printf " Case  %d :%s hash iterations FINISHED\n\n" "$ix" "${array[$ix]}"
    echo "Check that the last line was of %s iterations" "${array[$ix]}"
    tail -n 5 ./ThreadFiles/ThreadOutputFileThread1.txt
    sleep 4

done
echo

