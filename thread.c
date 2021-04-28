#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int n;
 void *thread1(void *a)
{int *b=(int *)a;
 int i,temp,flag=1,j=0;
while(flag==1 && j!=(n/2)-1)
{flag=0;
 i=0;

 while(i<(n/2)-1-j)
 {
   if(*(b+i) > *(b+i+1))
   {	temp=*(b+i);
	*(b+i)=*(b+i+1);
	*(b+i+1)=temp;
	flag=1;
   } 
   i++;
 }
 j++;

}
//for(i=0;i<(n/2)-1;i++)
//printf("%d",*(b+i));
pthread_exit(NULL);
}


void *thread2(void *a)
{int *b=(int *)a;
 int i,temp,flag=1,j=0,d=n%2;
while(flag==1 && j!=(n/2)-1+d)
{flag=0;
 i=0;
 while(i<(n/2)-1-j+d)
 {
   if(*(b+i) > *(b+i+1))
   {	temp=*(b+i);
	*(b+i)=*(b+i+1);
	*(b+i+1)=temp;
	flag=1;
   } 
   i++;
 }
 j++;
}


pthread_exit(NULL);
}

void main()
{int i,j,k,a[15],b[15];
pthread_t tid1,tid2;
printf("enter number of items");
scanf("%d",&n);
printf("enter the numbers");
for(i=0;i<n;i++)
scanf("%d",&a[i]);
pthread_create(&tid1,NULL,thread1,(void *)&a[0]);
pthread_create(&tid2,NULL,thread2,(void *)&a[n/2]);

i=0;
j=n/2;
k=0;
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
/*while(i<n/2 && j<n)
{
if(a[i]>a[j])
{b[k]=a[j];
j++;
k++;
}
else
{
b[k]=a[i];
i++;
k++;

}

}

if(i==n/2)
{
 while(k<n)
{
b[k]=a[j];
j++;
k++;
}
}
else
{
while(k<n)
{
b[k]=a[i];
i++;
k++;
}
}
*/
printf("\nsorted numbers");
for(i=0;i<n;i++)
printf("%d ",a[i]);
pthread_exit(NULL);
}
