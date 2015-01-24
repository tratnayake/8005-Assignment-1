
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>


//The struct's that will be passed to the executing thread form the main program that details it's name and how many iterations to hash for.
struct threadStruct
  {

              char* threadName;

              long iterations;

  }; 



/*----------- Function Prototypes ------------------*/
void* runTask (void*);

/*------------ Mutex Variables ---------------------*/
pthread_mutex_t printfLock = PTHREAD_MUTEX_INITIALIZER;



int main (int argc, char *argv[])
{

  // THis is the MAIN overall logfile that the threads will write only their START and END times to.
  FILE *pFile;
  pFile = fopen("./ThreadLogFile.txt","a");


  //time vars required to hold the time.
  time_t programStartTime;
  time_t programEndTime;

  //var that holds the amount of iterations.
  long hashIterations;

  // Check that the user has supplied a number of iterations to hash for.
  if (argc != 2)
      {   /* check for valid number of command-line arguments */ 
            fprintf(stderr, "Usage: %s hashing iterations\n", argv[1]);
            return 1; 
    } 

  hashIterations = atol(argv[1]);
     
  //Delete any existing log files
  system("exec rm -r ./ThreadFiles/*.txt"); 

  //assign the current time to var
  time(&programStartTime);

  //Print PROGRAM START TIME
  printf("** THREADS PROGRAM START** TIME: %s  \n\n",asctime( localtime(&programStartTime)));
  fprintf(pFile,"Threads\nIterations,%ld\nProgram Start,%s\n", hashIterations, ctime(&programStartTime));
  fflush(pFile);
  //fclose(pFile);

  //Create 5 threads.
  pthread_t thread1, thread2,thread3,thread4,thread5;
  
  //Create the thread structs
  struct threadStruct *Thread1;
  Thread1 = malloc(sizeof(struct threadStruct));
  Thread1->threadName = "Thread1";
  Thread1-> iterations = hashIterations;

  struct threadStruct *Thread2;
  Thread2 = malloc(sizeof(struct threadStruct));
  Thread2->threadName = "Thread2";
  Thread2-> iterations = hashIterations;

  struct threadStruct *Thread3;
  Thread3 = malloc(sizeof(struct threadStruct));
  Thread3->threadName = "Thread3";
  Thread3-> iterations = hashIterations;

  struct threadStruct *Thread4;
  Thread4 = malloc(sizeof(struct threadStruct));
  Thread4->threadName = "Thread4";
  Thread4-> iterations = hashIterations;

  struct threadStruct *Thread5;
  Thread5 = malloc(sizeof(struct threadStruct));
  Thread5->threadName = "Thread5";
  Thread5-> iterations = hashIterations;



  //Spawn the threads and supply the individual threadStructs
  pthread_create (&thread1, NULL, runTask, (void *) Thread1);
  pthread_create (&thread2, NULL, runTask, (void *) Thread2);
  pthread_create (&thread3, NULL, runTask, (void *) Thread3);
  pthread_create (&thread4, NULL, runTask, (void *) Thread4);
  pthread_create (&thread5, NULL, runTask, (void *) Thread5);
 
  //Join the threads to makesure that we wait till they finish to exit the program. 
  pthread_join (thread1, NULL);
  pthread_join (thread2, NULL);
  pthread_join (thread3, NULL);
  pthread_join (thread4, NULL);
  pthread_join (thread5, NULL);

  
  printf ("Threads Complete\n");

  time(&programEndTime);

  pFile = fopen("./ThreadLogFile.txt","a");
  printf("** THREADS PROGRAM END** TIME: %s  \n\n",asctime( localtime(&programEndTime)));
  fprintf(pFile,"Program End,%s\n", ctime(&programEndTime));
  

  return 0;
}

/*----------  Output Message Function -------------*/
void* runTask (void* threadObj)
{

  //Get the values from the struct.
  struct threadStruct *thread = (struct threadStruct*) threadObj;
  char* threadName = thread->threadName;
  long n = thread->iterations;
  long i;
  int x;

  FILE *fp;

  //sched_yield();

  //pthread_mutex_lock (&printfLock);

  //PASTE CODE


    //Vars required for the fileName and Looping
    //char fileNumString[sizeof(fileNum)];
    char loopCounterString[100];

  

    time_t threadStartTime;
    time_t threadEndTime;
    time_t iterationStartTime;
    time_t iterationEndTime;



    char outputFileName[1024];

    strcpy(outputFileName, "./ThreadFiles/ThreadTaskOutputFile");
    //Convert fileNum INT into a String
          //DEBUG: printf("Before convert,fileNumString: %s",fileNumString);
          // sprintf(fileNumString,"%d",fileNum);
          //DEBUG: printf("After convert,fileNumString: %s",fileNumString);
    strcat(outputFileName, threadName);
    strcat(outputFileName,".txt");

    char data[1024];    
    char hash[SHA_DIGEST_LENGTH];

    //DEBUG: printf("Before print, the fileOutputName is: %s",outputFileName);

    fp = fopen(outputFileName, "w");// "w" means that we are going to write on this file

    threadStartTime = time(NULL);
    printf("** %s START** TIME %s \n\n",threadName,asctime(localtime(&threadStartTime)));
    fprintf(fp, "%s START: TIME: %s \n", threadName, asctime(localtime(&threadStartTime)));
    //fprintf(pFile, "PROCESS %d start,%s \n", processID, asctime(localtime(&threadStart)));

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

  threadEndTime = time(NULL);
    printf("** %s END** TIME %s \n\n",threadName,asctime(localtime(&threadEndTime)));
    fprintf(fp, "%s END: TIME: %s \n", threadName, asctime(localtime(&threadEndTime)));







  //pthread_mutex_unlock (&printfLock);
  
   return NULL;
}

