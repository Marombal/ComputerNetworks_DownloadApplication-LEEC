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
 * @brief This function processes the URL, separating it into different elements and storing them in the respective places in the structure (connectionArgs *args)
 * 
 * @param url pointer to url string
 * @param args pointer to the struct where the information will be stored
 * @return ERROR (-1) on error; OK (1) on sucess 
 */
int parseArgs(char *url, connectionArgs *args);


/**
 * @brief Get the Ip object
 * 
 * @param host pointer to the string with the host from where IP will be search
 * @param args pointer to the struct with the information
 * @return ERROR (-1) on error; 0 on sucess  
 */
int getIp(char *host, connectionArgs *args);

/**
 * @brief Get the File Name object
 * 
 * @param args pointer to the struct with the information
 * @return ERROR (-1) on error; 0 on sucess  
 */
int getFileName(connectionArgs *args);


/**
 * @brief This function prints the arguments inside the struct (connectionArgs *args)
 * 
 * @param args pointer to the struct to print
 */
void printArgs(connectionArgs *args);


#endif