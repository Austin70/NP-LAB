#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <pthread.h>

#define THREAD_NUM 20
//sem_t reader;
sem_t writer;
int rc=0;
int wc=0;
pthread_t th[THREAD_NUM];
pthread_mutex_t mutex;



void* reads(void* args)
{
int shmid;
shmid=*((int *)args);
pthread_mutex_lock(&mutex);
printf("\nwait reader");
while(wc!=0);
printf("\nok reader");
rc++;
if(rc==1)
sem_wait(&writer);

//sem_post(&reader);

pthread_mutex_unlock(&mutex);

//critical section
char *str = (char*) shmat(shmid,NULL,0);
printf("\n%s",str);
shmdt(str);

//
pthread_mutex_lock(&mutex);
//sem_wait(&reader);
rc--;
if(rc==0)
sem_post(&writer);
pthread_mutex_unlock(&mutex);

}

void* writes(void* args)
{
wc++;
int shmid;
shmid=*((int *)args);
char string[50]="qwerty";
printf("\nwait");


sem_wait(&writer);

printf("\nOK");
	
//critical section

char *str = (char*) shmat(shmid,NULL,0);
printf("\nenter data");
//fgets(string,50,stdin);

strcat(str,string);
printf("\nData written");
shmdt(str);

//
sem_post(&writer);
wc--;
}





int main()
{

int ch=0,i;
char c;
//sem_init(&reader, 0, 0);
    sem_init(&writer, 0, 1);
pthread_mutex_init(&mutex, NULL);

key_t key = ftok("shmfile",65);
  int  shmid = shmget(key, 1024, 0666|IPC_CREAT);

for (i = 0; i < THREAD_NUM; i++) {
       // if (i > 0) {
if(i%2==0){//equal number of readers and writers
            if (pthread_create(&th[i], NULL, &writes, (void *)&shmid ) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &reads, (void *)&shmid ) != 0) {
                perror("Failed to create thread");
            }
        }
    }
for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

/*while(ch!=3){
printf("\nenter your choice\n1.reader\n2.writer\n3.exit\n");
scanf("%d",&ch);
scanf("%c",&c);
switch(ch)
{*/
/*case 1:reads(shmid);
	break;
case 2:writes(shmid);
	break;
case 3:break;
default :printf("choice error..try again");
	  
}

}
*/
//sem_destroy(&reader);
shmctl(shmid,IPC_RMID,NULL);
    sem_destroy(&writer);
pthread_mutex_destroy(&mutex);
return 0;
}
