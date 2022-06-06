#include "args.h"
#include "connection.h"

#define TCP_PORT 21

int main(int argc, char **argv){

    /* Verifica se recebeu input */
    if(argc != 2){
        fprintf(stderr, "usage: download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(1);  // exit(1) -> Exit Failure
    }
    
    
    connectionArgs args;
    int socketfd_data;
    int socketfd_control;
    char urlcpy[256];
    char command[256];
    char rd[1024];

    strcpy(urlcpy, argv[1]);

    memset(args.file_name, 0, 128);
    memset(args.host, 0, 128);
    memset(args.host_name, 0, 128);
    memset(args.ip, 0, 128);
    memset(args.password, 0, 128);
    memset(args.url_path, 0, 128);
    memset(args.user, 0, 128);

    
    if(parseArgs(urlcpy, &args) == ERROR){
        printf("usage: %s ftp://<user>:<password>@<host>/<url-path>\n", argv[0]);
        exit(1);
    }
    printArgs(&args);
    
    if(client_init(args.ip, TCP_PORT, &socketfd_control) == ERROR){
        printf("Error: clint_init() control\n");
        exit(1);
    }
    if(readResponse(socketfd_control, rd, sizeof(rd)) == ERROR){
        printf("Error: readResponse() /1\n");
        exit(1);
    }

    sprintf(command, "user %s\r\n", args.user);
        
    if(clientCommand(socketfd_control, command) == ERROR){
        printf("Error: clientCommand() /1\n");
        exit(1);
    }
    if(readResponse(socketfd_control, rd, sizeof(rd)) == ERROR){
        printf("Error: readResponse() /1\n");
        exit(1);
    }
    //printf("\n\naqui3\n\n");
    sprintf(command, "pass %s\r\n", args.password);

    if(clientCommand(socketfd_control, command) == ERROR){
        printf("Error: clientCommand() /x\n");
        exit(1);
    }
    if(readResponse(socketfd_control, rd, sizeof(rd)) == ERROR){
        printf("Error: readResponse() /x\n");
        exit(1);
    }

    char ip[32];
    int port;
    sprintf(command, "pasv\r\n");

    if(clientCommand(socketfd_control, command) == ERROR) {
        printf("Error: clientCommand() /2\n");
        exit(1);
    }
    if(pasvMode(socketfd_control, ip, &port) == ERROR) {
        printf("Error: pasvMode()\n");
        exit(1);
    }

    printf("IP: %s\nPort Number: %d\n", ip, port);
    
    if((client_init(ip, port, &socketfd_data)) == ERROR){
        printf("Error: client_init() [data]\n");
        exit(1);
    }
    sprintf(command, "retr %s\r\n", args.url_path);

    if(clientCommand(socketfd_control, command) == ERROR){ 
        printf("Error: clientCommand() /3\n");
        exit(1);
    }
    if(readResponse(socketfd_control, rd, sizeof(rd)) == ERROR) {
        printf("Error: readResponse() /2\n");
        exit(1);
    }

    if(writeFile(socketfd_data, args.file_name) == ERROR) {
        printf("Error: writeFile()\n");
        exit(1);
    }

    sprintf(command, "quit\r\n");
    if(clientCommand(socketfd_control, command) == ERROR){
        printf("Error: clientCommand() /4\n");
        exit(1);
    }
    if(readResponse(socketfd_control, rd, sizeof(rd)) == ERROR) {
        printf("Error: readResponse() /3\n");
        exit(1);
    }
    
    close(socketfd_control);
    close(socketfd_data);

    printf("\n\n");
    printf("##########################################################\n");
    printf("######################---> Done <---######################\n");
    printf("##########################################################\n");
    printf("\n\n");
    
    exit(0);     // exit(0) -> Exit Success
}

