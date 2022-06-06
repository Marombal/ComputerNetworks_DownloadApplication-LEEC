#ifndef CONNEC_H
#define CONNEC_H

#include "args.h"

/**
 * @brief Initiate the connection between client and server (by creating a connection socket)
 * 
 * @param ip  
 * @param port 
 * @param socketfd 
 * @return ERROR (0) on error; OK (1) on sucess  
 */
int client_init(char *ip, int port, int *socketfd);

/**
 * @brief not yet
 * 
 * @param socketfd 
 * @param command 
 * @return ERROR (0) on error; OK (1) on sucess  
 */
int clientCommand(int socketfd, char * command);

/**
 * @brief not yet
 * 
 * @param socketfd 
 * @param ip 
 * @param port 
 * @return ERROR (0) on error; OK (1) on sucess  
 */
int pasvMode(int socketfd, char *ip, int *port);


/**
 * @brief not yet
 * 
 * @param socketfd 
 * @param rd 
 * @param size 
 * @return ERROR (0) on error; OK (1) on sucess  
 */
int readResponse(int socketfd, char* rd, size_t size);

/**
 * @brief not yet
 * 
 * @param socketfd 
 * @param filename 
 * @return ERROR (0) on error; OK (1) on sucess 
 */
int writeFile(int socketfd, char* filename);

#endif