#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netdb.h> 

#define SIZE 128
#define OK 1
#define ERROR -1

typedef struct connectionArgs{
    char user[SIZE];
    char password[SIZE];
    char host[SIZE];
    char url_path[SIZE];
    char file_name[SIZE];
    char host_name[SIZE];
    char ip[SIZE];
} connectionArgs;

typedef enum {
    USERNAME,
    PASSWORD,
    HOSTNAME,
    FILE_PATH
} States;

/**
 * @brief Not Yet
 * 
 * @param url 
 * @param args 
 * @return int 
 */
int parseArgs(char *url, connectionArgs *args);


/**
 * @brief Get the Ip object
 * 
 * @param host 
 * @param args 
 * @return int 
 */
int getIp(char *host, connectionArgs *args);

/**
 * @brief Get the File Name object
 * 
 * @param args 
 * @return int 
 */
int getFileName(connectionArgs *args);


/**
 * @brief This function prints the arguments inside the struct (connectionArgs *args)
 * 
 * @param args pointer to the struct to print
 */
void printArgs(connectionArgs *args);


#endif