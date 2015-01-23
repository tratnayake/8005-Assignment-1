
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

int runTask(int fileNumber, long processNumber, long iterations, FILE *pFile);

int main (int argc, char *argv[]) 
{
    pid_t childpid = 0; 
    int i, n, status;

    long hashIterations;



  
    //pid_t pid;

    //Creating space for vars that will be used later to dicate fileNumber and Process Number in outputfiles.
    //char fileNumber[50];
    

    //For dateTime
    time_t programStartTime;
    time(&programStartTime);

    FILE *pFile;

    pFile = fopen("ProcessLogFile.txt","a");


    if (argc != 2)
      {   /* check for valid number of command-line arguments */ 
            fprintf(stderr, "Usage: %s hashing iterations\n", argv[0]);
            return 1; 
    }  

    //Delete any existing log files
    system("exec rm -r ./ProcessFiles/*.txt");   

    

    hashIterations = atol(argv[1]);
    n = 5;  

    printf("** PROCESSES PROGRAM WITH NUMBER OF ITERATIONS: %ld START TIME: %s \n", hashIterations, ctime(&programStartTime));
    fprintf(pFile,"Processes\nIterations,%ld\nProgram Start,%s\n", hashIterations, ctime(&programStartTime));
    fflush(pFile);

    for (i = 0; i < n; i++)
      if ((childpid = fork()) <= 0)
      break;
    
      //printf("ChildPID: %ld \n",(long)childpid);
      switch((long)childpid)
      {
        case -1:
          perror("ERROR!\n");
          break;

        case 0:
          //printf("I'm a child!\n");
          //fprintf(stderr, "**CHILD** i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
           //i, (long)getpid(), (long)getppid(), (long)childpid);

          runTask(i,(long)getpid(),hashIterations,pFile);

          break;

        default:
          //printf("I'm not a child?\n");
          //printf("**PARENT**: i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
           //i, (long)getpid(), (long)getppid(), (long)childpid);

          
          while (n > 0) {
            wait(&status);
            //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
            --n;  // TODO(pts): Remove pid from the pids array.
          }

          time_t programEndTime;

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
    strcpy(outputFileName, "./ProcessFiles/ProcessTaskOutputFile");
    //Convert fileNum INT into a String
          //DEBUG: printf("Before convert,fileNumString: %s",fileNumString);
    sprintf(fileNumString,"%d",fileNum);
          //DEBUG: printf("After convert,fileNumString: %s",fileNumString);
    strcat(outputFileName, fileNumString);
    strcat(outputFileName,".txt");

    char data[1024];    
    char hash[SHA_DIGEST_LENGTH];

    //DEBUG: printf("Before print, the fileOutputName is: %s",outputFileName);

    fp = fopen(outputFileName, "w");// "w" means that we are going to write on this file

    processStartTime = time(NULL);
    printf("** PROCESS: %d START** TIME %s \n\n",processID,asctime(localtime(&processStartTime)));
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
      //Print string+i
      //printf("Thing to hash is %s",data);
      iterationStartTime = time(NULL);
      fprintf(fp, "ITERATION %ld | TIME: %s \n", i, asctime (localtime(&iterationStartTime)) );
     
      
      SHA((unsigned char*) data,length,(unsigned char*) hash);



      //printf("The hash is %x \n",hash);
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
     //fprintf(pFile, "PROCESS %d end,%s \n", processID, asctime(localtime(&processEndTime)));
     //fflush(pFile);
     
    return 0; 
}
