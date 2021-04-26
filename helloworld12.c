#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


int main()
{
	pid_t pid, pid1, pid2,wpid;

	
	pid = fork();

	if (pid == 0) {

		
		sleep(5);

		
		printf("child[1] --> pid = %d and ppid = %d\n",getpid(), getppid());
	}

	else {
		pid1 = fork();
		if (pid1 == 0) {
			sleep(2);
			printf("child[2] --> pid = %d and ppid = %d\n",getpid(), getppid());
		}
		else {
			pid2 = fork();
			if (pid2 == 0) {
				
				printf("child[3] --> pid = %d and ppid = %d\n",getpid(), getppid());
			}

			
			else {
				
				while(wpid=wait(NULL)!=-1);//sleep(8);//Cannot use wait as parent will continue when any one child terminates
				printf("parent --> pid = %d\n", getpid());
			}
		}
	}

	return 0;
}

