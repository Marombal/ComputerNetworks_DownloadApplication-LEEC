#include "args.h"

int parseArgs(char *url, connectionArgs *args){
    if(!args){
        printf("Error parseArgs() invalid parameters\n");
        return ERROR;
    }


    char ftp_[] = "ftp://"; // "parte inicial da string"
    for(int i = 0; i < 6; i++){
        if(url[i] != ftp_[i]){
            printf("Usage: ftp://\n");
            return ERROR;
        }
    }
    
    int index = 6;
    int length = strlen(url);
    char curr_char;
    int arg_index = 0;
    States state = USERNAME;

    /* modo "anonimo" */
    if (strchr(url, '@') == NULL) 
    {
        //printf("aqui fixe\n");
        strncpy(args->user, "anonymous", 10);
        strncpy(args->password, "1234", 5); //qualquer coisa random
        state = HOSTNAME;
    }

    while(index < length){
        curr_char = url[index];
        switch (state)
        {
        case USERNAME:
            if(curr_char == ':'){
                args->user[arg_index] = '\0';
                arg_index = 0;
                state = PASSWORD;
            }
            else{
                args->user[arg_index] = curr_char;
                arg_index++;
            }
            break;
        case PASSWORD:
            if(curr_char == '@'){
                args->password[arg_index] = '\0';
                arg_index = 0;
                state = HOSTNAME;
            }
            else{
                args->password[arg_index] = curr_char;
                arg_index++;
            }
            break;
        case HOSTNAME:
            if(curr_char == '/'){
                args->host[arg_index] = '\0';
                arg_index = 0;
                state = FILE_PATH;
            }
            else{
                args->host[arg_index] = curr_char;
                arg_index++;
            }
        break;
        case FILE_PATH:
            args->url_path[arg_index] = curr_char;
            arg_index++;
            break;
        }
        index++;
    }

    if(getIp(args->host, args) != 0){
        printf("Error getIp()\n");
        return ERROR;
    }

    if(getFileName(args) != 0){
        printf("Error getFileName()\n");
        return ERROR;
    }

    return OK;
}

int getIp(char *host, connectionArgs *args){
    if(!args){
        printf("Error getIp() invalid parameters\n");
        return ERROR;
    }
    struct hostent *h;
    
    if((h = gethostbyname(host)) == NULL){
        herror("Error getting host name\n");
        return ERROR;
    }
    
    strcpy(args->host_name, h->h_name);
    strcpy(args->ip, inet_ntoa( *( ( struct in_addr *)h->h_addr) )); //32 bits Internet addr with net ordenation for dotted decimal notation 

    return 0;
}

int getFileName(connectionArgs *args){
    if(!args){
        printf("Error getFileName() invalid parameters\n");
        return ERROR;
    }
    char fullpath[256];
    strcpy(fullpath, args->url_path);

    char* aux = strtok(fullpath, "/");

    while(aux != NULL){
        strcpy(args->file_name, aux);
        aux = strtok(NULL, "/");
    }

    return 0; //returns 0 if success
}

void printArgs(connectionArgs *args){
    if(!args){
        printf("Error printArgs() invalid parameters\n");
        return;
    }
    printf("Information\n\n");
    printf("[Username: %s]\n", args->user);
    printf("[Password: %s]\n", args->password);
    printf("[Host: %s]\n", args->host);
    printf("[HostName: %s]\n", args->host_name);
    printf("[FileName: %s]\n", args->file_name);
    printf("[UrlPath: %s]\n", args->url_path);
    printf("[IpAdress: %s]\n\n\n", args->ip);
    return;
}