
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

// look up the sched_yield() system call

struct threadStruct
  {

              char* threadName;

              long iterations;

  };  /* note semi-colon here */



/*----------- Function Prototypes ------------------*/
void* runTask (void*);

/*------------ Mutex Variables ---------------------*/
pthread_mutex_t printfLock = PTHREAD_MUTEX_INITIALIZER;

int main (int argc, char *argv[])
{

  

  FILE *pFile;

  pFile = fopen("./ThreadLogFile.txt","a");

  time_t programStartTime;
  time_t programEndTime;

  long hashIterations;

  if (argc != 2)
      {   /* check for valid number of command-line arguments */ 
            fprintf(stderr, "Usage: %s hashing iterations\n", argv[1]);
            return 1; 
    } 

    //Delete any existing log files
    system("exec rm -r ./ThreadFiles/*.txt"); 

 hashIterations = atol(argv[1]);


  time(&programStartTime);

  printf("** THREADS PROGRAM START** TIME: %s  \n\n",asctime( localtime(&programStartTime)));
  fprintf(pFile,"Threads\nIterations,%ld\nProgram Start,%s\n", hashIterations, ctime(&programStartTime));
  fflush(pFile);
  //fclose(pFile);

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
  long hashIterations = thread->iterations;
  
  sched_yield();

  pthread_mutex_lock (&printfLock);

   int x;
   long i;

    //RUN FUNCTION HERE
   
   FILE *fp;
   //FILE *pFile;

   //pFile = fopen("./ThreadLogFile.txt","a");

   //Vars required to get currentDateTime
   time_t threadTime;
   time_t threadEndTime;
   time_t iterationStartTime;
   time_t iterationEndTime;
   


   char fileOutputString[100];
   strcpy(fileOutputString,"./ThreadFiles/ThreadOutputFile");
   strcat(fileOutputString,(char *) threadName);
   strcat(fileOutputString,".txt");

   fp = fopen(fileOutputString,"a");

   threadTime = time(NULL);
   printf("** %s START** TIME: %s  \n\n",(char*) threadName,asctime( localtime(&threadTime)));
   fprintf(fp, "THREAD START: %s TIME: %s \n", threadName, asctime(localtime(&threadTime)));
   //fprintf(pFile,"%s start,%s\n",(char*) threadName,asctime( localtime(&threadTime)));
   

 
   

    for (i = 1; i <= hashIterations; i++)
    {
      //printf("ITERATION %i START \n",i);
      //Convert i to a String
      //sprintf(loopCounterString,"%ld", i);
      char data[1024];    
      char hash[SHA_DIGEST_LENGTH];
      char loopCounterString[100];

      sprintf(loopCounterString,"%ld",i);
      strcpy(data, "HASHSTRING");
      //Add value of i  (concatenate) to END of string
      strcat(data,loopCounterString);
      size_t length = sizeof(data);
      //Print string+i
      
      SHA((unsigned char*) data,length,(unsigned char*) hash);


      iterationStartTime = time(NULL);
      fprintf(fp, "ITERATION %ld | START TIME: %s \n", i, asctime (localtime(&iterationStartTime)) );
     
      for(x = 0; x < sizeof(hash); x++ )
      {
    
        fprintf(fp,"%x", (char)hash[x]);
      }
      
      fprintf(fp,"\n");
  
      
       
        iterationEndTime = time(NULL);
        fprintf(fp, "ITERATION %ld | END TIME: %s \n", i, asctime (localtime(&iterationEndTime)));
     
      }

     //threadTime = time(NULL);
     threadEndTime = time(NULL);
      printf("** %s END** TIME: %s  \n\n",(char*) threadName,asctime( localtime(&threadEndTime) ) );
      fprintf(fp," %s END TIME: %s  \n\n",(char*) threadName,asctime( localtime(&threadEndTime) ) );
      //fprintf(pFile,"%s end,%s\n",(char*) threadName,asctime( localtime(&threadEndTime) ) );
      //fflush(pFile);
  
    //fclose(fp);


    pthread_mutex_unlock (&printfLock);
  
   return NULL;
}

