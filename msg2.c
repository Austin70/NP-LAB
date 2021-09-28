
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
int main() {

mqd_t q2;
char *buf;
struct mq_attr *attr1;
int prio;
attr1 = malloc(sizeof(struct mq_attr));

q2 = mq_open("/test_q",O_RDONLY);//READ ONLY

if(q2 == -1) 
{ printf("\nError");return 1;}


buf=malloc(20*sizeof(char));

if(mq_getattr(q2, attr1)==-1)
{printf("\nError getattr");return 1;}

mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);


mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);


mq_receive(q2,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\n Message = %s\n",buf);

return 0;
}

