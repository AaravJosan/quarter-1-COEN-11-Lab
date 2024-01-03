//new.c
#include "lab10.h"

void bin_read_from_file(char fileName[]) {
    FILE *fptr;
    pthread_mutex_lock(&mutex);
    fptr = fopen(fileName, "rb");

    if (fptr == NULL) {
        printf("File not found, creating new file\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    struct Node node;

    while(fread(&node, sizeof(struct Node), 1, fptr) == 1) {
        if(node.type == 0)
            printf("%s %s: %s. Birthday: %d/%d \n", node.fname, node.lname, node.number, node.extra.bday[0], node.extra.bday[1]);
        else if(node.type == 1)
            printf("%s %s: %s. Office phone: %s\n", node.fname, node.lname, node.number, node.extra.ophone);
        else if(node.type == 2)
            printf("%s %s: %s \n", node.fname, node.lname, node.number);
    }
    fclose(fptr);
    pthread_mutex_unlock(&mutex);
}

void *bin_write_to_file(void *arg) {
    char *fileName = (char *)arg;
    while (1) {
        sleep(15);

        pthread_mutex_lock(&mutex);

        FILE *fptr = fopen(fileName, "wb");
        if (fptr == NULL) {
            perror("error opening file");
            pthread_mutex_unlock(&mutex);
            continue;  
        }

        for (int i = 0; i < 3; i++) {
            struct Node *current = heads[i];
            while (current != NULL) {
                // Only write the struct Node, excluding extra data
                fwrite(current, sizeof(struct Node), 1, fptr);
                current = current->next;
            }
        }
        printf("Updated\n");
        fclose(fptr);
        pthread_mutex_unlock(&mutex);
    }
}
