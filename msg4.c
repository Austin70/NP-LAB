
  
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



typedef struct StudentDet {
  char name[30];
  char rno[5];
  int rank;
}Std;

int toInt(char* operand) {
  int val=0;
  int temp=0;
  int len=strlen(operand);
  for(int i=0;i<len;i++) {
    val*=10;
    val+=(operand[i]-'0');
  }
  return val;
}


void displayDetails(Std* s_details, int n) {
  for(int i=0;i<n;i++) {
    
    printf("Name: %s\n",s_details[i].name);
    printf("rno: %s\n",s_details[i].rno);
    printf("Rank: %d\n",s_details[i].rank);

  }
}

void get_string(char* str) {

  fgets(str,50,stdin);
  if(strcmp(str,"\n")==0) {
    fgets(str,50,stdin);
  }
  int str_len=strlen(str);
  if(str[str_len-1]=='\n') {
    str[str_len-1]='\0';
  }
}

void swap(Std* std1, Std* std2)
{
    Std temp;
    strcpy(temp.name,std1->name);
    strcpy(temp.rno,std1->rno);
    temp.rank=std1->rank;

    strcpy(std1->name,std2->name);
    strcpy(std1->rno,std2->rno);
    std1->rank=std2->rank;

    strcpy(std2->name,temp.name);
    strcpy(std2->rno,temp.rno);
    std2->rank=temp.rank;

}
void bubbleSort(Std* s_details, int n)
{
   int i, j;
   for (i = 0; i < n-1; i++) {
     for (j = 0; j < n-i-1; j++){
       if (s_details[j].rank > s_details[j+1].rank){
         swap(&s_details[j], &s_details[j+1]);
       }
     }
   }
}

int main() {
  char str[100];
  int n=0;
  Std* s_details = (Std*)malloc(10*sizeof(Std));
  key_t key = ftok("shmfile",65);
  int  shmid = shmget(key, 1024, 0666|IPC_CREAT);
  char *data_ptr = (char*) shmat(shmid,NULL,0);
  

  printf("Data read from memory: %s\n",data_ptr);

  

  int i=0;
  while(data_ptr[i]!='\0') {
    while(data_ptr[i]!=';') {
      int k=0;
      char name[10];
      char rno[5];
      char rank_str[5];
      while(data_ptr[i]!='|') {
        name[k]=data_ptr[i];
        k++;
        i++;
      }
      name[k]='\0';
      i++;
      k=0;
      while(data_ptr[i]!='|') {
        rno[k]=data_ptr[i];
        k++;
        i++;
      }
      rno[k]='\0';
      i++;
      k=0;
      while(data_ptr[i]!=';') {
        rank_str[k]=data_ptr[i];
        k++;
        i++;
      }
      rank_str[k]='\0';
      strcpy(s_details[n].name,name);
      strcpy(s_details[n].rno,rno);
      s_details[n].rank=toInt(rank_str);
      n++;
    }
    i++;
  }
  

  
  bubbleSort(s_details,n);
  displayDetails(s_details,n);
  shmdt(data_ptr); 

    // destroy the shared memory
 shmctl(shmid,IPC_RMID,NULL); //destroying the created segment,THUS removes data

return 0;
}

