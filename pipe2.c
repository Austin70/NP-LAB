
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int fd1[2];//P->C  
	int fd2[2];//C->P  

	
	
	int f,c;
	pid_t p;


	if (pipe(fd1)==-1)
	{
		printf("first Pipe Failed");
		return 1;
		
	}
	if (pipe(fd2)==-1)
	{
		printf("second Pipe Failed");
		return 1;
	}
	
	p = fork();

	if (p ==-1)
	{
		printf("fork Failed");
		return 1;
	}

	
	else if (p != 0)
	{       
		char input_str[100];
		printf("\nenter the string");
	        scanf("%s", input_str);
		char concat_str[100];

		close(fd1[0]); 
		close(fd2[1]); 

		
		f = sizeof(input_str)/ sizeof(char);
		write(fd1[1], input_str, f);

	close(fd1[1]);
		

		
		wait(NULL);

		 

		
		read(fd2[0], concat_str, 100);
		printf("After Concatenation %s\n", concat_str);
		close(fd2[0]);

}

	
	else
	{
		
		close(fd1[1]); 
		close(fd2[0]);
		char fixed_str[] = "Austin";
		
		char concat_str[100];
		read(fd1[0], concat_str, 100);
		close(fd1[0]);
		
		for (c=0; concat_str[c]!='\0'; c++)
		for (f=0; fixed_str[f]!='\0'; f++);
			

	

		
		
		
        
		
		
		write(fd2[1], concat_str, c);
		write(fd2[1], fixed_str,f+1);
		close(fd2[1]);

		
	}
}

