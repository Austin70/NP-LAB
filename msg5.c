#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct message
{
    long msg_type;
    char message[200];
    
} m;

int main()
{
    key_t key;
    key  = ftok("msg5",10);
    int msg_id;
    msg_id = msgget(key, 0666 | IPC_CREAT);
    m.msg_type = 1;
    printf("Enter the string: ");
    fgets(m.message, 180, stdin);
    printf("Recieved string is : %s\n", m.message);
    msgsnd(msg_id, &m, sizeof(struct message)-sizeof(long), 0);
return 0;
}
