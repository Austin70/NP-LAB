#include<stdio.h>
#include<unistd.h>

#include<string.h>






int main()
{   int a[3];
    int words=0,newline=0,characters=0;
    char str[200];
    int size=sizeof(str)/sizeof(char);
int fd1[2];//C->P
int fd2[2];//P->C
if(pipe(fd1)== -1){printf("\nerror fd1 pipe");}
if(pipe(fd2)== -1){printf("\nerror fd2 pipe");}

pid_t pid=fork();

if(pid==-1){printf("\nerror fork");return 1;}

else if(pid!=0)
{   

close(fd1[1]);
close(fd2[0]);
printf("\nenter sentence and stop using with ~\n");
    scanf("%[^~]",&str);
    
    if(write(fd2[1], str, size )==-1){printf("\nerror parent write");return 1;}
      printf("\nwrote the sentence to child\n ");
    close(fd2[1]);
    if(read(fd1[0],a,sizeof(int) *3)==-1){printf("\nerror parent read");return 1;}
    close(fd1[0]);
    
    
     printf("Total number of words : %d\n",a[0]);
     printf("Total number of lines : %d\n",a[1]);
     printf("Total number of characters : %d\n",a[2]);  
    
    

    
}
else
{

close(fd1[0]);
close(fd2[1]);
    if(read(fd2[0], str, size )==-1){printf("\nerror child read");return 1;}
    close(fd2[0]);
  for(int i=0;str[i]!='\0';i++)
     { 
         if(str[i] == ' ')
         { 
              words++;
         }
         else if(str[i] == '\n')
         {
             newline++;
              words++;
         }
         else if(str[i] != ' ' && str[i] != '\n')
         {
         characters++;
         }
     }
    if(characters > 0)//Corner case
    {
        words++;
        newline++;
    }
    a[0]=words;
     a[1]=newline;
      a[2]=characters;
      
      FILE * fp;
   
  
   fp = fopen ("Output.txt","w");
 
   
   
       fprintf (fp, "No of words %d\n",a[0]);
       fprintf (fp, "No of lines %d\n",a[1]);
       fprintf (fp, "No of characters %d\n",a[2]);
   
 
    
   fclose (fp);
    if(write(fd1[1], a, sizeof(int)*3 )==-1){printf("\nerror child write");return 1;}
    printf("\nwrote words to parent\n");
    
    close(fd1[1]);


}   

    


return 0;
}
