#include<stdio.h>
#include<unistd.h>

int main()
{
if(fork() || fork())
printf("forked\n");
}
