#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define MAX 15
int c1;
int r1;
int c2;
int r2;
int a[MAX][MAX];
int b[MAX][MAX];

void *multi()
{
static int i=0,j=0,k=0;
int d[MAX];



//for(k=0;k<r2;k++)
//	d[k]=a[i][k]*b[k][j];
if(k==r2)
{
j++;
k=0;
}

if(j==c2)
{	j=0;i++;}

d[0]=a[i][k]*b[k][j];
k++;
pthread_exit((void *)d[0]);
}






void main()
{int i,j,k,x[MAX],c[MAX][MAX],sum=0,sums[MAX];
int *p[MAX+MAX];
void **ptr;
int *q;
pthread_t tid[MAX];


printf("\nenter details of first matrix");
printf("\nenter number of rows");
scanf("%d",&r1);
printf("\nenter number of columns");
scanf("%d",&c1);
printf("\nenter the numbers");
for(i=0;i<r1;i++)
	for(j=0;j<c1;j++)
		scanf("%d",&a[i][j]);

printf("\nenter details of second matrix");
printf("\nenter number of rows");
scanf("%d",&r2);
printf("\nenter number of columns");
scanf("%d",&c2);
printf("\nenter the numbers");
for(i=0;i<r2;i++)
	for(j=0;j<c2;j++)
		scanf("%d",&b[i][j]);
if(c1!=r2)
{printf("\nmultiplication not possible");
exit(0);
}
for(i=0;i<c2*r1*r2;i++)
{

pthread_create(&tid[i], NULL, multi, NULL);

pthread_join(tid[i],(void **)&p[i]);
//printf("%d",p[i]);
x[i]=p[i] ;

}
k=0;
for(i=0;i<c2*r1*r2;i++)
{
 for(j=0;j<c1;j++,i++)
 {;sum+=x[i];}
sums[k]=sum;
k++;
sum=0;
 i--;   
}

k=0;
for(i=0;i<r1;i++)
{   printf("\n"); 
    for(j=0;j<c2;j++)
     {  printf("%d\t",c[i][j]=sums[k]);k++;}

}   
}
