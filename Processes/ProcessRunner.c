/* ----------------------------------------------------------------------------
SOURCE FILE

Name:           ProcessRunner.c

Program:        a1 (COMP 8005, Threads vs Processes)

Developer:      Thilina Ratnayake

Due date:       26 Jan 2015

Functions:
        int main (int argc, char* argv[])
        int runTask(int fileNumber, long processNumber, long iterations, FILE *pFile)


Description:
        This program gets invoked by the Processes.sh script and runs the task with 5 
        child processes for the desired amount of iterations.


---------------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

/*----------- Function Prototypes ------------------*/
int runTask(int fileNumber, long processNumber, long iterations, FILE *pFile);

int main (int argc, char *argv[]) 
{
    pid_t childpid = 0; 
    int i, n, status;
    long hashIterations;
    time_t programStartTime;
    time_t programEndTime;
    FILE *pFile;

    //"The 'Main' log file that is present for all the iterations.
    pFile = fopen("ProcessLogFile.txt","a");


    if (argc != 2)
      {   /* check for valid number of command-line arguments */ 
            fprintf(stderr, "Usage: %s hashing iterations\n", argv[0]);
            return 1; 
    }  

    //Delete any existing log files
    system("exec rm -r ./ProcessFiles/*.txt");   

    //Set hashIterations to user input.
    hashIterations = atol(argv[1]);

    //The amount of children to create
    n = 5;  

    time(&programStartTime);
    printf("** PROCESSES PROGRAM WITH NUMBER OF ITERATIONS: %ld START TIME: %s \n", hashIterations, ctime(&programStartTime));
    fprintf(pFile,"Processes\nIterations,%ld\nProgram Start,%s\n", hashIterations, ctime(&programStartTime));
    fflush(pFile);

    //Fork the required amount of children
    for (i = 0; i < n; i++){
      if ((childpid = fork()) <= 0)
      break;
    }
    
      //switch on the PID's provided by the fork.
      switch((long)childpid)
      {
        //If an error occured during the fork.
        case -1:
          perror("ERROR!\n");
          break;

        //If a child
        case 0:
          runTask(i,(long)getpid(),hashIterations,pFile);
          break;

        //Parent
        default:
            
          //Wait for all children to finish
          while (n > 0) {
            wait(&status);
            --n;  
          }


          time(&programEndTime);
          
          //printf("PROGRAM END TIME: %s \n", ctime(&programEndTime));
          fprintf(pFile,"Program End,%s\n", ctime(&programEndTime));
          printf("** PROGRAM END TIME, %s \n", ctime(&programEndTime));

              break;
          }

    return 0; 
}

int runTask(int fileNumber, long processNumber, long iterations, FILE *pFile){
   
    FILE *fp;
    //Vars taken from Program Start
    int fileNum = fileNumber;
    int processID = processNumber;
    long i,n;
    int x;
    n = iterations;
    //Vars required for the fileName and Looping
    char fileNumString[sizeof(fileNum)];
    char loopCounterString[100];
    time_t processStartTime;
    time_t processEndTime;
    time_t iterationStartTime;
    time_t iterationEndTime;
    char outputFileName[1024];
    char data[1024];    
    char hash[SHA_DIGEST_LENGTH];


    //Craft the output file names e.g. ./ProcessFiles/ProcessTaskOutputFile1.txt
    strcpy(outputFileName, "./ProcessFiles/ProcessTaskOutputFile");
    //Convert fileNum INT into a String
    sprintf(fileNumString,"%d",fileNum);
    strcat(outputFileName, fileNumString);
    strcat(outputFileName,".txt");

    processStartTime = time(NULL);
    printf("** PROCESS: %d START** TIME %s \n\n",processID,asctime(localtime(&processStartTime)));
    fp = fopen(outputFileName, "w");// "w" means that we are going to write on this file
    fprintf(fp, "PROCESS START: processID: %d TIME: %s \n", processID, asctime(localtime(&processStartTime)));
    //fprintf(pFile, "PROCESS %d start,%s \n", processID, asctime(localtime(&processStartTime)));

    //RUN FUNCTION HERE
    for (i = 1; i <= n; i++)
    {
      //Convert i to a String
      sprintf(loopCounterString,"%ld", i);
      strcpy(data, "HASHSTRING");
      //Add value of i  (concatenate) to END of string
      strcat(data,loopCounterString);
      size_t length = sizeof(data);
      iterationStartTime = time(NULL);
      fprintf(fp, "ITERATION %ld | TIME: %s \n", i, asctime (localtime(&iterationStartTime)) );
     
      //HASH
      SHA((unsigned char*) data,length,(unsigned char*) hash);

      fprintf(fp,"PLAINTEXT: %s\n",data);
      fprintf(fp,"HASH:\n");

      for(x = 0; x < sizeof(hash); x++ )
      {
        fprintf(fp,"%x", (char)hash[x]);
      }
      
      fprintf(fp,"\n");
      
        iterationEndTime = time(NULL);
       fprintf(fp, "ITERATION %ld | END TIME: %s \n", i, asctime (localtime(&iterationEndTime)));
     
    }

  processEndTime = time(NULL);
    printf("** PROCESS: %d END** TIME %s \n\n",processID,asctime(localtime(&processEndTime)));
    fprintf(fp, "PROCESS END: processID: %d TIME: %s \n", processID, asctime(localtime(&processEndTime)));
  
    return 0; 
}
