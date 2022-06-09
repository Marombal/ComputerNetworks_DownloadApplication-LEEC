#ifndef CONNEC_H
#define CONNEC_H

#include "args.h"

/**
 * @brief Initiate the connection between client and server (by creating a connection socket)
 * 
 * @param ip pointer to the IP
 * @param port port number
 * @param socketfd pointer to socket file descriptor
 * @return ERROR (-1) on error; OK (1) on sucess  
 */
int client_init(char *ip, int port, int *socketfd);

/**
 * @brief not yet
 * 
 * @param socketfd pointer to socket file descriptor
 * @param command 
 * @return ERROR (-1) on error; OK (1) on sucess  
 */
int clientCommand(int socketfd, char * command);

/**
 * @brief not yet
 * 
 * @param socketfd pointer to socket file descriptor
 * @param ip pointer to the IP
 * @param port port number
 * @return ERROR (-1) on error; OK (1) on sucess  
 */
int pasvMode(int socketfd, char *ip, int *port);


/**
 * @brief not yet
 * 
 * @param socketfd pointer to socket file descriptor
 * @param rd 
 * @param size size of rd
 * @return ERROR (-1) on error; OK (1) on sucess  
 */
int readResponse(int socketfd, char* rd, size_t size);

/**
 * @brief not yet
 * 
 * @param socketfd pointer to socket file descriptor
 * @param filename 
 * @return ERROR (-1) on error; OK (1) on sucess 
 */
int writeFile(int socketfd, char* filename);

#endif