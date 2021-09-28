#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

void sort(int *a,int n)
{
    int i,j,temp;
    for(i =1;i<n;i++) 
    {
        temp=a[i];
        j=i-1;
         while(a[j]>temp&&j>= 0)
        {
            a[j+1]=a[j];
            j=j-1;
        }
        a[j+1]=temp;
    }
}
int main()
{
int fd1[2];//C1->P
int fd2[2];//P->C1
int fd3[2];//C2->P
int fd4[2];//P->C2
int fd5[2];//C3->P
int fd6[2];//P->C3

int s1,s2,s3;

int a[100],b[35],c[35],d[35],n,i,j=0,k=0,l=0,m=0,p=0;
int t1=0,t2=0;
s1=sizeof(b)/sizeof(int);
s2=sizeof(c)/sizeof(int);
s3=sizeof(d)/sizeof(int);

pid_t pid;
pid=getpid();

if(pipe(fd1)== -1)
{printf("\nerror fd1 pipe");}

if(pipe(fd2)== -1)
{printf("\nerror fd2 pipe");}
pipe(fd3);
pipe(fd4);
pipe(fd5);
pipe(fd6);
printf("\nenter n\n");
scanf("%d",&n);

if(n%3==1)
    t1=1;
else if(n%3==2)
    {t1=1;t2=1;}
if(fork())
{
	if(fork())
	{
		if(fork())
		{	close(fd1[1]);
			close(fd2[0]);
			close(fd3[1]);
			close(fd4[0]);
			close(fd5[1]);
			close(fd6[0]);
						
			
			printf("\nenter values\n");
			for(i=0;i<n;i++)
			{scanf("%d",&a[i]);
					
			}
			i=0;
			while(i!=n)
			{
				if(i%3==0)
				{	b[j]=a[i];
					j++;
					
					
				}
				else if(i%3==1)
				{c[k]=a[i];
					k++;
				}
				else
				{d[l]=a[i];
					l++;
				}
			i++;
			}
			write(fd2[1],b,s1);
			write(fd4[1],c,s2);
			write(fd6[1],d,s3);
            while(wait(NULL)!=-1);
		}
		else
		{
		 
		 read(fd6[0],d,s3);
		 sort(d,n/3);
		for(i=0;i<(n/3);i++)
		printf("%d;",d[i]);
		write(fd5[1],d,s3);
		}	
	}
	else
	{
	    read(fd4[0],c,s2);
	    sort(c,n/3+t2);
		for(i=0;i<(n/3)+t2;i++)
		printf("%d'",c[i]);
		write(fd3[1],c,s2);
	}

}
else
{
  read(fd2[0],b,s1);
  sort(b,n/3+t1);
		for(i=0;i<(n/3)+t1;i++)
		printf("%d|",b[i]);
		write(fd1[1],b,s1);
}

if(pid==getpid())
{
read(fd1[0],b,s1);
read(fd3[0],c,s2);
read(fd5[0],d,s3);
printf("\nfirst subset%d",b[n/3+t1-1]);
printf("\nsecond subset%d",c[n/3+t2-1]);
printf("\nthird subset%d",d[n/3-1]);
for(int i=0;i<j;i++)
{
a[i]=b[i];
    
}
for(int i=j;m<k;i++,m++)
{
a[i]=c[m];
    
}
for(int i=j+k;p<l;i++,p++)
{
a[i]=d[p];
    
}
sort(a,n);

for(i=0;i<n;i++)
			{printf("\n%d",a[i]);
					
			}
}

}
