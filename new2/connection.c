#include "connection.h"

int client_init(char *ip, int port, int *socketfd){ //dado
    
    struct sockaddr_in server_addr;

    //server addr handling
    bzero((char*)&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);	// 32 bit Internet address network byte ordered
	server_addr.sin_port = htons(port);		        // server TCP port must be network byte ordered 

    //open TCP connection
    if((*socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket()");
        return ERROR;
    }

    //connect to server
    if(connect(*socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("connect()");
        return ERROR;
    }

    return OK;
}

int clientCommand(int socketfd, char * command){    //client sends commands to socket to be received and read in server
    int tam;
    if((tam = write(socketfd, command, strlen(command))) <= 0){
        printf("Error: command not sent\n");
        return ERROR;
    }
    printf("< %s\n", command);
    return OK;
}

int pasvMode(int socketfd, char *ip, int *port){    //pasvMode command reception (saves IP and Port number)
    char buf[1024];

    
    if(readResponse(socketfd, buf, sizeof(buf)) == ERROR){
       printf("Error: cannot enter passive mode\n");
       return ERROR;
    }

    //< 227 Entering Passive Mode (193,136,28,12,19,91), example
    //printf("\n\nbud antes: %s \n\n", buf);
    //printf("......");puts(buf);

    strtok(buf, "("); // pega no buf que tem< 227 Entering Passive Mode (193,136,28,12,19,91) e corta ate 193,136,28,12,19,91)

    //printf("\n\nbuf apos: %s \n\n", buf);
    char* ip1 = strtok(NULL, ",");
    //printf("......");puts(ip1);
    char* ip2 = strtok(NULL, ",");
    char* ip3 = strtok(NULL, ",");
    char* ip4 = strtok(NULL, ",");
    //guarda os numeros nos ips... ip 1 = 193, ip2 = 136 etc

    //printf(":::::");
    sprintf(ip, "%s.%s.%s.%s", ip1, ip2, ip3, ip4);

    char* aux1 = strtok(NULL, ",");
    char* aux2 = strtok(NULL, ")");

    *port = (256 * atoi(aux1)) + atoi(aux2);

    return OK;
}


int readResponse(int socketfd, char* rd, size_t size){  //reading the different commands responses from server to client
    char aux[3];
    long num;
    FILE* fd;

    if(!(fd = fdopen(socketfd, "r"))){
        printf("Error opening file to read\n");
        return ERROR;
    }
    
    do{
        memset(rd, 0, size);
        rd = fgets(rd, size, fd);
        printf("%s", rd);
    } while(rd[3] != ' ');

    strncpy(aux, rd, 3);
    num = atoi(aux);

    //printf("num: %ld", num); //debug

    if(num > 420 && num < 554){
        printf("Command error - «400» (command not accepted and requested action did not take place) or «500» (syntax error, command unrecognized and the requested action did not take place)\n");
        return ERROR;
    }

    return OK;
}


int writeFile(int socketfd, char* filename){    //writing on socketfile the communication between client and server
    int bytes;
    char buf[1024];

    FILE* fd;

    if(!(fd = fopen(filename, "w"))){
        printf("Error opening file to write\n");
        return ERROR;
    }

    while((bytes = read(socketfd, buf, sizeof(bytes))) > 0){
        if(bytes < 0){
            printf("Error: Nothing received from data socket\n");
            return ERROR;
        }
        if((fwrite(buf, bytes, 1, fd)) < 0){
            printf("Error writting file in socketfile\n");
            return ERROR;
        }
    }

    fclose(fd);

    return OK;
}