
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

                        int iterations;

            };  /* note semi-colon here */


/*----------- Function Prototypes ------------------*/
void* task (void*);

/*------------ Mutex Variables ---------------------*/
pthread_mutex_t printfLock = PTHREAD_MUTEX_INITIALIZER;

int main (void)
{

  FILE *pFile;

  pFile = fopen("./ThreadLogFile.txt","w");

  time_t programStartTime;
  time_t programEndTime;

  long hashIterations;

  if (argc != 2)
      {   /* check for valid number of command-line arguments */ 
            fprintf(stderr, "Usage: %s hashing iterations\n", argv[1]);
            return 1; 
    } 

 hashIterations = atol(argv[1]);


  programStartTime = time(NULL);

  printf("** THREADS PROGRAM START** TIME: %s  \n\n",asctime( localtime(&programStartTime)));
  fprintf(pFile,"** THREADS PROGRAM START** TIME: %s  \n\n",asctime( localtime(&programStartTime)));
  fflush(pFile);
  fclose(pFile);

  pthread_t thread1, thread2,thread3,thread4,thread5;
  const char* msg1 = "Thread1";
  const char* msg2 = "Thread2";
  const char* msg3 = "Thread3";
  const char* msg4 = "Thread4";
  const char* msg5 = "Thread5";

  //Create the thread structs
  struct threadStruct *Thread1;
  *Thread1.threadName = "Thread1";
  *Thread1.iterations = hashIterations;

  struct threadStruct *Thread2;
  *Thread2.threadName = "Thread2";
  *Thread2.iterations = hashIterations;

  struct threadStruct *Thread3;
  *Thread3.threadName = "Thread3";
  *Thread3.iterations = hashIterations;

  struct threadStruct *Thread4;
  *Thread4.threadName = "Thread4";
  *Thread4.iterations = hashIterations;

  struct threadStruct *Thread5;
  *Thread5.threadName = "Thread5";
  *Thread5.iterations = hashIterations;






  pthread_create (&thread1, NULL, task, (void*)Thread1);
  pthread_create (&thread2, NULL, task, (void*)Thread2);
  pthread_create (&thread3, NULL, task, (void*)Thread3);
  pthread_create (&thread4, NULL, task, (void*)Thread4);
  pthread_create (&thread5, NULL, task, (void*)Thread5);

  pthread_join (thread1, NULL);
  pthread_join (thread2, NULL);
  pthread_join (thread3, NULL);
  pthread_join (thread4, NULL);
  pthread_join (thread5, NULL);

  //printf ("Threads Complete\n");

  programEndTime = time(NULL);

  pFile = fopen("./ThreadLogFile.txt","a");
  printf("** THREADS PROGRAM END** TIME: %s  \n\n",asctime( localtime(&programEndTime)));
  fprintf(pFile,"** THREADS PROGRAM END** TIME: %s  \n\n",asctime( localtime(&programEndTime)));
  

  return 0;
}

/*----------  Output Message Function -------------*/
void* task (void* ThreadStruct.threadName)
{

    sched_yield();

    pthread_mutex_lock (&printfLock);




   int i,x;

    //DEBUG: printf("Before print, the fileOutputName is: %s",outputFileName);

    //fp = fopen(outputFileName, "w");// "w" means that we are going to write on this file

    //fprintf(fp, "PROCESS START:  %d TIME: %s \n",  asctime (timeinfo));
     //fprintf(pFile, "PROCESS START:  %d TIME: %s \n",  asctime (timeinfo));

    //RUN FUNCTION HERE
   
   FILE *fp;
   FILE *pFile;

   pFile = fopen("ThreadLogFile.txt","a");

   //Vars required to get currentDateTime
   time_t threadTime;
   time_t threadEndTime;
   threadTime = time(NULL);

   printf("** %s START** TIME: %s  \n\n",(char*) ThreadStruct.threadName,asctime( localtime(&threadTime)));
   fprintf(pFile," %s START TIME: %s  \n\n",(char*) ThreadStruct.threadName,asctime( localtime(&threadTime)));
   fflush(pFile);

   char fileOutputString[100];
   strcpy(fileOutputString,"./ThreadFiles/ThreadOutputFile");
   strcat(fileOutputString,(char *) ThreadStruct.threadName);
   strcat(fileOutputString,".txt");

   //printf("Output file is %s",fileOutputString);
   //fileOutputString = "./TheadFiles/ThreadOutputFile";

   fp = fopen(fileOutputString,"a");

    for (i = 1; i <= 10000000; i++)
    {
      //printf("ITERATION %i START \n",i);
      //Convert i to a String
      //sprintf(loopCounterString,"%ld", i);
      unsigned char data[1024];    
      unsigned char hash[SHA_DIGEST_LENGTH];
      char loopCounterString[100];

      sprintf(loopCounterString,"%d",i);
      strcpy(data, "HASHSTRING");
      //Add value of i  (concatenate) to END of string
      strcat(data,loopCounterString);
      size_t length = sizeof(data);
      //Print string+i
      //printf("Thing to hash is %s",data);
      //fprintf(fp, "ITERATION %ld, TIME: %s \n", i,  asctime (timeinfo) );
      //strcat(fileOutputString, "./TheadFiles/ThreadOutputFile");
      //strcat(fileOutputString,loopCounterString);
      //strcat(fileOutputString,".txt");
      //printf("FileOutputSTring is %s\n", fileOutputString);

     //printf("Thing to hash is %s\n",data); 
      SHA(data,length,hash);



      //printf("The hash is %x \n",hash);

      //printf("HASH:\n");
      fprintf(fp,"ITERATION START %d INSIDE THREAD: %d \n",i,(char *) ThreadStruct.threadName);
      fprintf(fp,"PLAINTEXT: %s\n",data);
      fprintf(fp, "HASH:\n");

      for(x = 0; x < sizeof(hash); x++ )
      {
     
        //printf("%x", (char)hash[x]);
        fprintf(fp,"%x", (char)hash[x]);
      }
      
      fprintf(fp,"\n");
      //printf("\n\n");
      
      
       //fprintf(fp, "END ITERATION %ld INSIDE PROCESS TIME: %s \n", i, asctime (timeinfo));
    
      //printf("ITERATION %i END \n\n",i); 
      fprintf(fp,"ITERATION END %d INSIDE THREAD: %d \n\n",i,(char *) ThreadStruct.threadName);
    }

     //threadTime = time(NULL);
     threadEndTime = time(NULL);
      printf("** %s END** TIME: %s  \n\n",(char*) ThreadStruct.threadName,asctime( localtime(&threadEndTime) ) );
      fprintf(pFile," %s END TIME: %s  \n\n",(char*) ThreadStruct.threadName,asctime( localtime(&threadEndTime) ) );
      fflush(pFile);
  
    //fclose(fp);


    pthread_mutex_unlock (&printfLock);
  
   return NULL;
}

