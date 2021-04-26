#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{	
	int fact=1,i=0,n=0,temp;

  while((temp=*(argv[1]+i))!=0)//ascii value of null character is zero
{	temp-=48;
	n=n*10+temp;//making it into decimal number from each character
	i++;
}

i=2;	
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
