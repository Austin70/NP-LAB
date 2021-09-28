#include <fcntl.h>           //for 0_* constants like 0_CREAT
#include <sys/stat.h>        // for mode constants 0666
#include <mqueue.h>
#include <stdio.h>
#include<string.h>
				//link with -lrt during compilation
				//gcc -lrt filename.c

int main() {

	mqd_t q1;
	
	
	char buf1[20];
	char buf2[20];
	char buf3[20];
	
	
	int pr1,pr2,pr3;
	printf("Input message one : ");
	fgets(buf1,20,stdin);

	printf("\n Input message two : ");
	fgets(buf2,20,stdin);

	printf("\n Input message three : ");
	fgets(buf3,20,stdin);
	

	
	printf("\n Input the priority of msg1: ");
	scanf("%d",&pr1);
	
	printf("\n Input the priority of msg2: ");
	scanf("%d",&pr2);
	
	printf("\n Input the priority of msg3: ");
	scanf("%d",&pr3);
	
	q1 = mq_open("/test_q",O_CREAT|O_WRONLY,0666,NULL);    //(Open for WRITE ONLY-O_WRONLY) creates new posix message queue or opens an existing queue
	if(q1 == -1) {
	 printf("Error");
	}

	
	
	mq_send(q1,buf1,20,pr1);
	mq_send(q1,buf2,20,pr2);
	mq_send(q1,buf3,20,pr3);
	
	
return 0;
}

/*#include <mqueue.h>


mqd_t mq_open(const char *name, int oflag);

or

       mqd_t mq_open(const char *name, int oflag, mode_t mode,
                     struct mq_attr *attr);

mq_open() does not add or remove messages from the queue.On success, mq_open() returns a message queue descriptor. On failure it returns (mqd_t)-1

The mq_open() function establishes the connection between a process and a message queue with a message queue descriptor. It creates an open message queue description that refers to the message queue, and a message queue descriptor that refers to that open message queue description

The name argument points to a string naming a message queue. The name string must begin with a slash character (/) and must conform to the rules for constructing a a path name. Processes calling mq_open() with the same value of name refer to the same message queue object, as long as that name has not been removed.

If name not the name of an existing message queue and creation is not requested, mq_open() fail and returns error.

POSIX_MQ_OPEN_MAX, defined in the limits.h header, specifies the maximum number of message queues that can exist system wide.

The oflag argument requests the desired receive and/or send access to the message queue. The requested access permission to receive or send messages is granted if the calling process would be granted read or write access, respectively, to an equivalently protected file.

The value of oflag is the bitwise-inclusive OR of values from the following list. One (and only one) of the first three access modes listed must be included in the value of oflag:

O_RDONLY 
Opens the message queue for receiving messages. The process can use the returned message queue descriptor with the mq_receive() function, but not with the mq_send() function. A message queue may be open multiple times in the same or different processes for receiving messages.

O_WRONLY 
Opens the queue for sending messages. The process can use the returned message queue descriptor with the mq_send() function but not with the mq_receive() function. A message queue may be open multiple times in the same or different processes for sending messages.

O_RDWR 
Opens the queue for both receiving and sending messages. The process can use any of the functions allowed for O_RDONLY and O_WRONLY. A message queue may be open multiple times in the same or different processes for sending messages.

 Zero or more of the following flags can additionally be ORed in
       oflag:

       O_CLOEXEC 
              Set the close-on-exec flag for the message queue
              descriptor.  See open(2) for a discussion of why this flag
              is useful.

       O_CREAT
              Create the message queue if it does not exist.  The owner
              (user ID) of the message queue is set to the effective
              user ID of the calling process.  The group ownership
              (group ID) is set to the effective group ID of the calling
              process.


		Creates a message queue. When this flag is specified, mq_open() also requires the mode and attr arguments. The mode argument is of type mode_t, while the attr attribute is a pointer to a mq_attr structure. If a message queue created with the name argument already exists, this flag is ignored (except as described under O_EXCL). If attr is NULL, mq_open() creates the message queue with the default message queue attributes: 10 messages, each of size _POSIX_PIPE_BUF. If attr is non-NULL and the calling process has the appropriate privilege on name, mq_open() sets mq_maxmsg and mq_msgsize attributes of the created queue to the values of the corresponding members in the mq_attr structure pointed to by attr. If attr is non-NULL and the calling process does not have the appropriate privilege on name, mq_open() fails without creating a message queue.

       O_EXCL If O_CREAT was specified in oflag, and a queue with the
              given name already exists, then fail with the error
              EEXIST.

		If both the O_EXCL and O_CREAT flags are set in oflag, mq_open() fails if the message queue name already exists. The check for the existence of the message queue and the creation of the message queue if it does not exist is atomic with respect to other threads executing mq_open() naming the same name with O_EXCL and O_CREAT set.

       O_NONBLOCK
              Open the queue in nonblocking mode.  In circumstances
              where mq_receive(3) and mq_send(3) would normally block,
              these functions instead fail with the error EAGAIN.

		Determines whether an mq_send() or mq_receive() function waits for resources or messages that are not currently available, or fails with errno set to EAGAIN. See the mq_receive() and mq_send() reference pages for more details.





*/
