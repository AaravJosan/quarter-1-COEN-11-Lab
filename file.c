//file.c
#include <stdio.h>
#include <ctype.h>
#include "lab10.h"

void add(char firstName[], char lastName[], char phoneNumber[], int choice, union info more) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->fname, firstName);
    strcpy(newNode->lname, lastName);
    strcpy(newNode->number, phoneNumber);
    newNode->type = choice;

    if (choice == 0) {
        newNode->extra.bday[0] = more.bday[0];
        newNode->extra.bday[1] = more.bday[1];
    }
    else if (choice == 1) {
        strcpy(newNode->extra.ophone, more.ophone);
    }

    int lastNameAscii = lastName[0];
    if(lastNameAscii >= 97 && lastNameAscii <= 107){
        if(heads[0] == NULL){
            heads[0] = newNode;
            return;
        }
        newNode -> next = heads[0];
        heads[0] = newNode;
        sort();
    }

    //l to r
    else if(lastNameAscii >= 108 && lastNameAscii <= 114){
        if(heads[1] == NULL){
            heads[1] = newNode;
            return;
        }
        newNode -> next = heads[1];
        heads[1] = newNode;
        sort();
    }

    //s to z
    else if(lastNameAscii >= 115 && lastNameAscii <= 122){
        if(heads[2] == NULL){
            heads[2] = newNode;
            return;
        }
        newNode -> next = heads[2];
        heads[2] = newNode;
        sort();
    }
}

void read_from_file(char fileName[], int key) {
    pthread_mutex_lock(&mutex);
    FILE *fptr;
    fptr = fopen(fileName, "r");

    if (fptr == NULL) {
        printf("File not found, creating new file\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    char fname[10], lname[10], number[11];
    union info extra;
    char fromFile[50];
    char temp[50];
    int type;
    while(fgets(fromFile, 50 ,fptr)) {
        int i;
        for(i = 0; i < strlen(fromFile); i++) {
            temp[i] = fromFile[i] ^ key;
        }
        char tempType;
        char *token = strtok(temp, " ");
        strcpy(fname, token);
        token = strtok(NULL, " ");
        strcpy(lname, token);
        token = strtok(NULL, " ");
        strcpy(number, token);
        token = strtok(NULL, " ");
        tempType = *token;
        int type = atoi(&tempType);

        if(type == 0){
            char month[4], day[10];
            token = strtok(NULL, " ");
            strcpy(month, token);
            extra.bday[0] = atoi(month);
            token = strtok(NULL, " ");
            strcpy(day, token);
            extra.bday[1] = atoi(day);
        }
        else if(type == 1){
            char a[21];
            token = strtok(NULL, " ");
            strcpy(a, token);
            char ophone[21];
            int i = 0; 
            while(*token != '\0'){
                if(isdigit(*token)){
                    ophone[i] = *token;
                }
                else
                    break;
                token++;
                i++;
            }
            strcpy(extra.ophone, ophone);
        }

        add(fname, lname, number, type, extra);
    }

    fclose(fptr);
    sort();
    pthread_mutex_unlock(&mutex);
}


void save_to_file(char fileName[], int key){
    pthread_mutex_lock(&mutex);
    FILE *fptr;
    fptr = fopen(fileName, "w");

    if(fptr == NULL){
        printf("File not found\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    for(int i = 0; i < 3; i++){
        struct Node *current = heads[i];
        while(current != NULL){
            char buffer[50];
            char temp[50];
            int j = 0;
            if (current->type == 0){
                sprintf(buffer, "%s %s %s %d %d %d", current->fname, current->lname, current->number, current->type, current->extra.bday[0], current->extra.bday[1]);
                for(j = 0; j < strlen(buffer); j++){
                     temp[j] = buffer[j] ^ key;
                }
                fprintf(fptr, "%s\n", temp);
            }
            else if(current -> type == 1){
                sprintf(buffer, "%s %s %s %d %s", current->fname, current->lname, current->number,current->type, current->extra.ophone);
                for(j = 0; j < strlen(buffer); j++){
                    temp[j] = buffer[j] ^ key;
                }
                fprintf(fptr, "%s\n", temp);
            }
            else if(current -> type == 2){
                sprintf(buffer, "%s %s %s %d", current->fname, current->lname, current->number, current->type);  
                for(j = 0; j < strlen(buffer); j++){
                    temp[j] = buffer[j] ^ key;
                }
                fprintf(fptr, "%s\n", temp);
            }
            current = current -> next;
        }
    }
    fclose(fptr);
    pthread_mutex_unlock(&mutex);
}