#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include <ctype.h>

struct message
{
    long msg_type;
    char message[200];

} m;

int main(){
    key_t key;
    key  = ftok("msg5",10);
 
    int msg_id = msgget(key, 0666 | IPC_CREAT);
    msgrcv(msg_id, &m, sizeof(struct message)-sizeof(long), 1, 0);
    printf("Recieved string is : %s\n", m.message);
    int n=strlen(m.message);
    n=n-1;
    int flag = 1;
    for (int s = 0; s < n / 2; s++) {
        if (tolower(m.message[s]) != tolower(m.message[n-1-s])) {
            flag = 0;
            break;
        }
    }
    if(flag)
        printf("string is palindrome");
    else
        printf("string is not palindrome");
 
    msgctl(msg_id, IPC_RMID, NULL);
return 0;
}
