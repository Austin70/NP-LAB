#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



//Student structure
typedef struct StudentDet {
  char name[30];
  char rno[5];
  int rank;
}Std;

//reading input from stdin
void get_string(char* str) {

  fgets(str,50,stdin);

  int str_len=strlen(str);
  if(str[str_len-1]=='\n') {
    str[str_len-1]='\0';
  }
}

//collecting details of n students
void collectStudentDetails(Std* s_details, int n) {
  for(int i=1;i<=n;i++) {
    printf("\nDetails of Student %d\n",i);
    printf("Enter name: ");
    get_string(s_details[i-1].name);
    printf("Enter rno: ");
    get_string(s_details[i-1].rno);
    printf("Enter rank: ");
    scanf("%d",&s_details[i-1].rank);
  
char ch;  
scanf("%c",&ch);//to remove \n
  }
}

//displaying all the collected details
void displayDetails(Std* s_details, int n) {
  for(int i=0;i<n;i++) {
    printf("\nStudent no: %d\n",i+1);
    printf("Name: %s\n",s_details[i].name);
    printf("rno: %s\n",s_details[i].rno);
    printf("Rank: %d\n",s_details[i].rank);

  }
}
//combinging deatils of one student
void combineOneStudent(Std stud,char* str) {
  sprintf(str,"%s|%s|%d;",stud.name,stud.rno,stud.rank);
}

//combining all the deatils
void combineAllStudents(Std* s_details, int n, char*str) {
  char temp_str[20];
  for(int i=0;i<n;i++) {
    combineOneStudent(s_details[i],temp_str);
    strcat(str,temp_str);
  }
}

int main() {
  

  Std* s_details;
  key_t key = ftok("shmfile",65);
  int  shmid = shmget(key, 1024, 0666|IPC_CREAT);
  int n;
  char str[100];
  printf("Enter the number of students ");
  scanf("%d",&n);
  char ch;  
scanf("%c",&ch);//to remove \n
  char *data_ptr = (char*) shmat(shmid,NULL,0);//casting
  s_details = (Std*)malloc(n*sizeof(Std));
  collectStudentDetails(s_details, n);

  printf("Collected Details\n");
  displayDetails(s_details, n);
  combineAllStudents(s_details, n, data_ptr);
  //data_ptr=str;

  printf("Data send: %s\n",data_ptr );
  shmdt(data_ptr);
  
return 0;
}
