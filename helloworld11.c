#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{	
	int fact=1,i=2,n;
	n=*argv[1];
	n-=48;
	while((i-2)<n)
	{
	
	
		if(fork()==0)
		{	printf("%d, ",fact);
			exit(0);		
			
		}
		else
           	{	wait(NULL);
			fact*=i++;
		}
	}
	printf("\b\b");
	return 0;
}

