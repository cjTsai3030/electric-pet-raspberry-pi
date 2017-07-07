#include <stdio.h>
#include <wiringPi.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h>

#define left1 7
#define left2 0
#define right1 2
#define right2 3
 
pthread_attr_t attr;
pthread_t tid;

static void* go(void *input)
{
	char *ctrl;
	while(1) {
	ctrl = (char*) input;
	switch (ctrl[0]) {
        case '1'    :
                digitalWrite(left1, HIGH);
                digitalWrite(left2, LOW);
                digitalWrite(right1, LOW);
                digitalWrite(right2, HIGH);
                break;
        case '2'  :
                digitalWrite(left1, LOW);
                digitalWrite(left2, HIGH);
                digitalWrite(right1, HIGH);
                digitalWrite(right2, LOW);
                break;
        case '3'  :
                digitalWrite(right1, LOW);
                digitalWrite(right2, HIGH);
                digitalWrite(left1, LOW);
                digitalWrite(left2, LOW);
                break;
        case '4' :
                digitalWrite(left1, HIGH);
                digitalWrite(left2, LOW);
                digitalWrite(right1, LOW);
		break;
	case 'q' :
		return input;
		break;
	}
	delay(2);
	digitalWrite(left1, LOW);
        digitalWrite(left2, LOW);
        digitalWrite(right1, LOW);
        digitalWrite(right2, LOW);
	delay(1);
	}
	return input;
}

int main (void)
{
  if (wiringPiSetup () == -1)
    return 1 ;
 
  pinMode (left1, OUTPUT);
  pinMode (left2, OUTPUT);
  pinMode (right1, OUTPUT);
  pinMode (right2, OUTPUT); 
 
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);

/* int i;
for(i=0; i<20; i++) {
	digitalWrite(left1, HIGH);
	digitalWrite(left2, LOW);
	digitalWrite(right1, LOW);
	digitalWrite(right2, HIGH);
	delay(3);

	digitalWrite(left1, LOW);
	digitalWrite(left2, LOW);
	digitalWrite(right1, LOW);
	digitalWrite(right2, LOW);
	delay(1);
}*/
    char client_message[100];
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, &go, &client_message);
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    void *res;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
    {
	printf("client = %s", client_message);
	/*switch (client_message[0]) {
        case '1'    :
                digitalWrite(left1, HIGH);
                digitalWrite(left2, LOW);
                digitalWrite(right1, LOW);
                digitalWrite(right2, HIGH);
                break;
        case '2'  :
                digitalWrite(left1, LOW);
                digitalWrite(left2, HIGH);
                digitalWrite(right1, HIGH);
                digitalWrite(right2, LOW);
                break;
        case '3'  :
                digitalWrite(right1, LOW);
                digitalWrite(right2, HIGH);
		digitalWrite(left1, LOW);
		digitalWrite(left2, LOW);
                break;
        case '4' :
                digitalWrite(left1, HIGH);
                digitalWrite(left2, LOW);
		digitalWrite(right1, LOW);
		digitalWrite(right2, LOW);
                break;
	}
	delay(10);
	//default  :
		digitalWrite(left1, LOW);
		digitalWrite(left2, LOW);
		digitalWrite(right1, LOW);
		digitalWrite(right2, LOW);
	//	break;
    	//}
	delay(5);*/

    }
    pthread_join(tid, &res);
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    return 0 ;
}
